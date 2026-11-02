#include <stdlib.h>
#include <stdio.h>

#include "simulator.h"
#include "particle.h"
#include "event.h"

struct Simulator_t
{
    int width;
    int height;
    int maxNumParticles;
    int numberOfParticles;
    double time;
    bool hasStarted;
    bool predictionsReady;


    Particle **particles;
    Event **nextEvent;

};



//Elle renvoie le prochain évènement d'une particule donnée
static Event *particleGetNextEvent(Particle *p, Simulator *s) //Trouve le premier évenement d'une particule donnée et le met à jour
{
    EventType type = NONE;
    Particle *other = NULL;
    double best = INFINITY_TIME;

    double xTime = particleGetXWallCollisionTime(p, s->width);
    if (xTime >= 0 && s->time + xTime < best)
    {
        best = s->time + xTime;
        type = XWALL;
    }
    double yTime = particleGetYWallCollisionTime(p, s->height);
    if (yTime >= 0 && s->time + yTime < best)
    {
        best = s->time + yTime;
        type = YWALL;
    }
    for (int j = 0; j < s->numberOfParticles; j++)
    {
        Particle *otherParticle = s->particles[j];
        if (otherParticle == p)
            continue;
        double collTime = particleGetCollisionTime(p, otherParticle);
        if (collTime >= 0 && s->time + collTime < best)
        {
            best = s->time + collTime;
            type = COLLISION;
            other = otherParticle;
        }
    }

    return eventCreate(type, p, other, best);
}

static void setPrediction(Simulator *s, Particle *particle)
{
    int index = -1;
    for (int i = 0; i < s->numberOfParticles; i++)
    {
        if (s->particles[i] == particle)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
        return;

    Event *e = particleGetNextEvent(s->particles[index], s);
    
    eventFree(s->nextEvent[index]);
    s->nextEvent[index] = e;
}



Simulator *simulatorCreate(double width, double height, int maxNumParticles)
{
    Simulator *s = malloc(sizeof(Simulator));

    if (!s)
    {
        fprintf(stderr, "simulatorCreate: allocation error.\n");
        exit(1);
    }

    s->particles = calloc((size_t) maxNumParticles, sizeof(*s->particles));
    s->nextEvent = calloc((size_t) maxNumParticles, sizeof(*s->nextEvent));
    if (!s->particles || !s->nextEvent)
    {
        fprintf(stderr, "simulatorCreate: allocation error.\n");
        free(s->particles);
        free(s->nextEvent);
        free(s);
        exit(1);
    }

    s->width = width;
    s->height = height;
    s->maxNumParticles = maxNumParticles;
    s->numberOfParticles = 0;
    s->hasStarted = false;
    s->time = 0;



    return s;
}

void simulatorFree(Simulator *s)
{
    for (int i = 0; i < s->numberOfParticles; i++){
        particleFree(s->particles[i]);
        eventFree(s->nextEvent[i]);
    }
    
    free(s->particles);
    free(s->nextEvent);
    free(s);
}

double simulatorGetHeight(Simulator *s)
{
    return s->height;
}

double simulatorGetWidth(Simulator *s)
{
    return s->width;
}

int simulatorGetNumCollisions(Simulator *s)
{
    int numColl=0;
    for (int i = 0; i < s->numberOfParticles; i++)
    {
        numColl += particleGetNumCollisions(s->particles[i]);
    }
    
    return numColl;
}

double simulatorGetElapsedTime(Simulator *s)
{
    return s->time;
}

int simulatorGetNumberOfParticles(Simulator *s)
{
    return s->numberOfParticles;
}

bool simulatorAddParticle(Simulator *s, Particle *p)
{

    if (s->numberOfParticles == s->maxNumParticles)
    {
        return false;
    }
    if (particleOutside(p, s->width, s->height))
    {
        return false;
    }
    if (s->hasStarted)
    {
        return false;
    }
    for (int i = 0; i < s->numberOfParticles; i++)
    {
        if (particleOverlap(p, s->particles[i]))
        {
            return false;
        }
    }

    s->particles[s->numberOfParticles] = p;
    s->numberOfParticles++;
    return true;
}

Particle *simulatorGetParticle(Simulator *s, int index)
{
    return s->particles[index];
}






//Calcul pour particule changées


Event *simulatorGetNextEvent(Simulator *s)
{
     
    if(!s->hasStarted){//Si la simulation n'a pas encore commencé,
        for (int i = 0; i < s->numberOfParticles; i++) //On initialise les prédictions pour toutes les particules
        {
            
            setPrediction(s, s->particles[i]);
        }
    }

    s->hasStarted = true;//La simulations commence au permier appel
    
    Event *best = NULL;//On cherche le meilleur évenement
    double bestTime = INFINITY_TIME;

    for (int i = 0; i < s->numberOfParticles; i++) //On parcourt toutes les particules pour trouver le meilleur évenement
    {
        Event *e = s->nextEvent[i];
        if (eventGetTime(e) < bestTime)
        {
            bestTime = eventGetTime(e);
            best = e;
        }
    }
    if(!best){
        best = eventCreate(NONE, NULL, NULL, INFINITY_TIME);
    }
    return best;
}

void simulatorStep(Simulator *s, double dt)
{
    double endTime=s->time+dt;

    while(s->time < endTime){
        Event *nextEvent = simulatorGetNextEvent(s);
        double eventTime = eventGetTime(nextEvent);

        if(eventGetType(nextEvent)==NONE||eventTime>endTime){ //Si il n'y a pas d'évenement ou si le prochain évenement 
            double restantTime=endTime-(s->time);             //est après la fin du pas de temps, on avance toutes les 
            for (int i = 0; i < s->numberOfParticles; i++)    //particules jusqu'à la fin du pas de temps
            {
                particleMove(s->particles[i],restantTime);
            }
            s->time=endTime;
            return;
        }

        double timeToEvent= eventTime-(s->time); //On calcule le temps restant avant l'évenement

        for (int i = 0; i < s->numberOfParticles; i++) //On avance toutes les particules jusqu'à l'évenement
        {
            particleMove(s->particles[i],timeToEvent);
        }

        s->time=eventTime; //On met à jour le temps de la simulation

        if (eventGetType(nextEvent) == XWALL) //On gère l'évenement selon son type
        {
            particleHandleXWallCollision(eventGetParticle1(nextEvent));
        }
        else if (eventGetType(nextEvent) == YWALL)
        {
            particleHandleYWallCollision(eventGetParticle1(nextEvent));
        }
        else if (eventGetType(nextEvent) == COLLISION)
        {
            particleHandleCollision(eventGetParticle1(nextEvent), eventGetParticle2(nextEvent));
        }

        for (int i = 0; i < s->numberOfParticles; i++)
            setPrediction(s, s->particles[i]);
        
    }

}



double simulatorStatParticles(Simulator *s, double (*f)(Particle *))
{
    double mean = 0;
    for (int i = 0; i < s->numberOfParticles; i++)
    {
        mean = mean + f(s->particles[i]);
    }
    mean = mean/((double)s->numberOfParticles);
    return mean;
}
