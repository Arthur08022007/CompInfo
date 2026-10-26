#include <stdlib.h>
#include <stdio.h>

#include "simulator.h"
#include "particle.h"
#include "event.h"

struct Simulator_t{
    int width;
    int height;
    int maxNumParticles;
    int numCollisions;
    int numberOfParticles;
    bool hasStarted;

    Particle *particles[];
};

Simulator *simulatorCreate(double width, double height, int maxNumParticles){
    Simulator *s=malloc(sizeof(Simulator)+maxNumParticles*sizeof(Particle *));

    if (!s)
    {
        fprintf(stderr, "simulatorCreate: allocation error.\n");
        exit(1);
    }


    s->width=width;
    s->height=height;
    s->maxNumParticles=maxNumParticles;
    s->numCollisions=0;
    s->numberOfParticles=0;
    s->hasStarted=false;

    return s;
}

void simulatorFree(Simulator *s){
    free(s);
}

double simulatorGetHeight(Simulator *s){
    return s->height;
}

double simulatorGetWidth(Simulator *s){
    return s->width;
}

int simulatorGetNumCollisions(Simulator *s){
    return s->numCollisions;
}

double simulatorGetElapsedTime(Simulator *s){
    return ;
}

int simulatorGetNumberOfParticles(Simulator *s){
    return s->numberOfParticles;
}

bool simulatorAddParticle(Simulator *s, Particle *p){

    if(s->numberOfParticles==s->maxNumParticles ){
        return false;
    }
    if(particleOutside(p,s->width,s->height)){
        return false;
    }
    if(s->hasStarted){
        return false;
    }
    for (int i=0;i<s->numberOfParticles;i++){
        if(particleOverlap(p, s->particles[i])){
            return false;
        }
    }
    
    s->particles[s->numberOfParticles]=p;
    s->numberOfParticles++;
    return true;

}