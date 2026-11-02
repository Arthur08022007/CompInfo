#include <stdlib.h>
#include <stdio.h>

#include "simulator.h"
#include "particle.h"
#include "event.h"
//la fonction de mise à jour prends en arguments un sim et un event

struct Simulator_t
{
    double width;
    double height;
    int maxNumParticles;
    int numberOfParticles;
    double time;
    bool hasStarted;

    Particle **particles;
    Event **nextEvents;
};

static Event *particleSearchNextEvent(Particle *p, Simulator *s)
{
    Event *e = eventCreate(NONE, NULL, NULL, INFINITY_TIME);
    double earliestTime = INFINITY_TIME;

    for (int i = 0; i < s->numberOfParticles; i++)
    {
        if (p == s->particles[i])
            continue;

        double collisionTime = particleGetCollisionTime(p, s->particles[i]);
        if (collisionTime >= 0 && collisionTime < earliestTime)
        {
            earliestTime = collisionTime;
            eventSet(e, COLLISION, p, s->particles[i], s->time + collisionTime);
        }
    }

    double xWallCollisionTime = particleGetXWallCollisionTime(p, s->width);
    if (xWallCollisionTime >= 0 && xWallCollisionTime < earliestTime)
    {
        earliestTime = xWallCollisionTime;
        eventSet(e, XWALL, p, NULL, s->time + xWallCollisionTime);
    }

    double yWallCollisionTime = particleGetYWallCollisionTime(p, s->height);
    if (yWallCollisionTime >= 0 && yWallCollisionTime < earliestTime)
    {
        earliestTime = yWallCollisionTime;
        eventSet(e, YWALL, p, NULL, s->time + yWallCollisionTime);
    }

    return e;
}

static void updateNextEvent(Simulator *s, Event *e)
{
    if (eventGetType(e) == NONE)
    {
        return;
    }

    for (int i = 0; i < s->numberOfParticles; i++)
    {
        if (s->particles[i] == eventGetParticle1(e) ||
            s->particles[i] == eventGetParticle2(e))
        {
            s->nextEvents[i] = e;
        }
    }
}

Simulator *simulatorCreate(double width, double height, int maxNumParticles)
{
    Simulator *s = malloc(sizeof(Simulator) +
                          maxNumParticles * (sizeof(Particle *) + sizeof(Event *)));

    if (!s)
    {
        fprintf(stderr, "simulatorCreate: allocation error.\n");
        exit(1);
    }

    s->width = width;
    s->height = height;
    s->maxNumParticles = maxNumParticles;
    s->numberOfParticles = 0;
    s->hasStarted = false;
    s->time = 0;
    s->particles = (Particle **)(s + 1);
    s->nextEvents = (Event **)(s->particles + maxNumParticles);
    for (int i = 0; i < maxNumParticles; i++)
    {
        s->particles[i] = NULL;
        s->nextEvents[i] = NULL;
    }

    return s;
}

void simulatorFree(Simulator *s)
{
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
    
    return numColl / 2;
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
    if (s->hasStarted)
    {
        return false;
    }
    
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
    if (index >= s->numberOfParticles)
    {
        return NULL;
    }
    return s->particles[index];
}

Event *simulatorGetNextEvent(Simulator *s)
{
    s->hasStarted=true;
    Event *e = eventCreate(NONE, NULL, NULL, INFINITY_TIME);
    double earliestTime = INFINITY_TIME;
    for (int i = 0; i < s->numberOfParticles; i++)
    {
        if (s->nextEvents[i] == NULL)
        {
            s->nextEvents[i] = particleSearchNextEvent(s->particles[i], s);
        }
        if (eventGetTime(s->nextEvents[i]) <= earliestTime)
        {
            earliestTime = eventGetTime(s->nextEvents[i]);
            e = s->nextEvents[i];
        }
    }
    return e;
}

void simulatorStep(Simulator *s, double dt)
{
    s->hasStarted=true;
    double endTime=s->time+dt;
    

    while(s->time < endTime){
        //on regadrde qui est le prochain évènement
        Event *nextEvent = simulatorGetNextEvent(s);

        double eventTime= eventGetTime(nextEvent);//Temps absolu


        //Si pas d'event ou temps trop loin; on avance juste les particules du temps restant
        if(eventGetType(nextEvent)==NONE||eventTime>=endTime){
            double restantTime=endTime-(s->time);
            for (int i = 0; i < s->numberOfParticles; i++)
            {
                particleMove(s->particles[i],restantTime);
            }
            s->time=endTime;
            if (eventGetType(nextEvent) == NONE)
            {
                eventFree(nextEvent);
            }
            return;
        }

        double timeToEvent= eventTime-(s->time); //temps relatif

        //On avance les particules jusqu'à l'event
        for (int i = 0; i < s->numberOfParticles; i++)
        {
            particleMove(s->particles[i],timeToEvent);
        }

        s->time=eventTime;

        //On exécute l'event
        if (eventGetType(nextEvent) == XWALL)
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
        

        if (eventGetParticle1(nextEvent))
        {
            Event *next = particleSearchNextEvent(eventGetParticle1(nextEvent), s);
            updateNextEvent(s, next);
        }
        if (eventGetParticle2(nextEvent))
        {
            Event *next = particleSearchNextEvent(eventGetParticle2(nextEvent), s);
            updateNextEvent(s, next);
        }
        eventFree(nextEvent);



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