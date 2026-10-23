#include <stdlib.h>
#include <stdio.h>
#include "particle.h"
#include "vector.h"
#include "color.h"

struct Particle_t
{
    double radius;
    double mass;
    Vector position;
    Vector velocity;
    Color color;
};

Particle *particleCreate(double radius, double mass, Vector position, Vector velocity, Color color){
    Particle *p=malloc(sizeof(Particle));

    if (!p)
    {
        fprintf(stderr, "particleCreate: allocation error.\n");
        exit(1);
    }

    p->radius=radius;
    p->mass=mass;
    p->position=position;
    p->velocity=velocity;
    p->color=color;

    return p;
}

void particleFree(Particle *p){
    free(p);
}

double particleGetRadius(Particle *p){
    return p->radius;
}

double particleGetMass(Particle *p){
    return p->mass;
}

Vector particleGetPosition(Particle *p){
    return p->position;
}

Vector particleGetVelocity(Particle *p){
    return p->velocity;
}

Color particleGetColor(Particle *p){
    return p->color;
}

double particleKineticEnergy(Particle *p){
    return p->mass*(vectorNorm(p->velocity)*vectorNorm(p->velocity))/2;
}


