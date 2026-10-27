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

    /* Événement NONE renvoyé quand rien ne peut se produire. */
    Event *nextEvent;

    Particle *particles[];
};

/* Premier événement impliquant p, stocké sur la particule. */
static void rebuildPrediction(Simulator *s, Particle *p)
{
    EventType type = NONE;
    Particle *partner = NULL;
    double best = INFINITY_TIME;

    double xTime = particleGetXWallCollisionTime(p, s->width);
    if (xTime > 0 && s->time + xTime < best)
    {
        best = s->time + xTime;
        type = XWALL;
    }
    double yTime = particleGetYWallCollisionTime(p, s->height);
    if (yTime > 0 && s->time + yTime < best)
    {
        best = s->time + yTime;
        type = YWALL;
    }
    for (int j = 0; j < s->numberOfParticles; j++)
    {
        Particle *other = s->particles[j];
        if (other == p)
            continue;
        double collTime = particleGetCollisionTime(p, other);
        if (collTime > 0 && s->time + collTime < best)
        {
            best = s->time + collTime;
            type = COLLISION;
            partner = other;
        }
    }
    eventSet(particleGetNextEvent(p), type, p, partner, best);
}

static void ensurePredictions(Simulator *s)
{
    s->hasStarted = true;
    if (s->predictionsReady)
        return;

    for (int i = 0; i < s->numberOfParticles; i++)
    {
        Particle *p = s->particles[i];
        particleSetNextEvent(p, eventCreate(NONE, NULL, NULL, INFINITY_TIME));
        rebuildPrediction(s, p);
    }
    s->predictionsReady = true;
}

static Event *findNextEvent(Simulator *s)
{
    Event *best = NULL;
    double bestTime = INFINITY_TIME;

    for (int i = 0; i < s->numberOfParticles; i++)
    {
        Event *e = particleGetNextEvent(s->particles[i]);
        if (eventGetTime(e) < bestTime)
        {
            bestTime = eventGetTime(e);
            best = e;
        }
    }
    return best;
}

/* Recalcule les prédictions des particules dont la vitesse a changé, et
 * celles dont l'événement mémorisé impliquait l'une d'elles. b vaut NULL
 * si l'événement est un mur. */
static void refreshAfterEvent(Simulator *s, Particle *a, Particle *b)
{
    rebuildPrediction(s, a);
    if (b)
        rebuildPrediction(s, b);

    for (int k = 0; k < s->numberOfParticles; k++)
    {
        Particle *p = s->particles[k];
        if (p == a || p == b)
            continue;
        Particle *partner = eventGetParticle2(particleGetNextEvent(p));
        if (partner == a || (b && partner == b))
            rebuildPrediction(s, p);
    }
}

Simulator *simulatorCreate(double width, double height, int maxNumParticles)
{
    Simulator *s = malloc(sizeof(Simulator) + maxNumParticles * sizeof(Particle *));

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
    s->predictionsReady = false;
    s->time = 0;
    s->nextEvent = eventCreate(NONE, NULL, NULL, INFINITY_TIME);

    return s;
}

void simulatorFree(Simulator *s)
{
    for (int i = 0; i < s->numberOfParticles; i++)
        particleFree(s->particles[i]);
    eventFree(s->nextEvent);
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

Event *simulatorGetNextEvent(Simulator *s)
{
    ensurePredictions(s);

    Event *best = findNextEvent(s);
    if (!best)
    {
        eventSet(s->nextEvent, NONE, NULL, NULL, INFINITY_TIME);
        return s->nextEvent;
    }
    return best;
}

void simulatorStep(Simulator *s, double dt)
{
    s->hasStarted=true;
    ensurePredictions(s);
    double endTime=s->time+dt;

    while(s->time < endTime){
        Event *nextEvent = simulatorGetNextEvent(s);
        double eventTime = eventGetTime(nextEvent);

        if(eventGetType(nextEvent)==NONE||eventTime>endTime){
            double restantTime=endTime-(s->time);
            for (int i = 0; i < s->numberOfParticles; i++)
            {
                particleMove(s->particles[i],restantTime);
            }
            s->time=endTime;
            return;
        }

        double timeToEvent= eventTime-(s->time);

        for (int i = 0; i < s->numberOfParticles; i++)
        {
            particleMove(s->particles[i],timeToEvent);
        }

        s->time=eventTime;

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

        refreshAfterEvent(s, eventGetParticle1(nextEvent), eventGetParticle2(nextEvent));
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
