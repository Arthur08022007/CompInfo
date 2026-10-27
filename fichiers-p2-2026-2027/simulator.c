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

    Particle *particles[];
};

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
    s->time = 0;

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
    Event *e = eventCreate(NONE, NULL, NULL, INFINITY_TIME);
    double earliestTime = INFINITY_TIME;
    for (int i = 0; i < s->numberOfParticles; i++)
    {
        double xTime= particleGetXWallCollisionTime(s->particles[i], s->width);
        if (xTime < earliestTime && xTime>0)
        {
            earliestTime = xTime;
            eventSet(e, XWALL,s->particles[i],NULL,s->time+xTime);
        }
        double yTime= particleGetYWallCollisionTime(s->particles[i], s->height);
        if (yTime < earliestTime && yTime>0)
        {
            earliestTime = yTime;
            eventSet(e, YWALL,s->particles[i],NULL,s->time+yTime);
        }
        for (int j = i+1; j < s->numberOfParticles; j++)
        {
            double collTime=particleGetCollisionTime(s->particles[i], s->particles[j]);
            if ( collTime < earliestTime && collTime>0)
            {
                earliestTime = collTime;
                eventSet(e, COLLISION, s->particles[i], s->particles[j], s->time + collTime);
            }
        }
    }
    return e;
}

void simulatorStep(Simulator *s, double dt)
{
    s->hasStarted=true;
    double endTime=s->time+dt;
    

    while(s->time < endTime){
        Event *nextEvent = simulatorGetNextEvent(s);

        double eventTime= eventGetTime(nextEvent) - s->time;

        if(eventGetType(nextEvent)==NONE||eventTime>endTime){
            double restantTime=endTime-(s->time);
            for (int i = 0; i < s->numberOfParticles; i++)
            {
                particleMove(s->particles[i],restantTime);
            }
            s->time=endTime;
            eventFree(nextEvent);
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