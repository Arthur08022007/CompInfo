#include <stdlib.h>
#include <stdio.h>
#include "particle.h"
#include "vector.h"
#include "color.h"
#include "math.h"

struct Particle_t
{
    double radius;
    double mass;
    Vector position;
    Vector velocity;
    Color color;
    double numCollision;
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
    p->numCollision=0;

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

double particleGetNumCollisions(Particle *p){
    return p->numCollision;
}

double particleKineticEnergy(Particle *p){
    return p->mass*(vectorNorm(p->velocity)*vectorNorm(p->velocity))/2;
}

void particleMove(Particle *p,double dt){
    p->position=vectorSum(vectorMultByScalar(p->velocity,dt),p->position);
}

void particleHandleCollision(Particle *p1, Particle *p2){
    p1->velocity=vectorSum(p1->velocity, vectorMultByScalar(vectorDiff(p2->position,p1->position),vectorDotProduct(vectorDiff(p2->velocity,p1->velocity),vectorDiff(p2->position,p1->position))*2.0*(p2->mass)/((p1->mass+p2->mass)*vectorNorm(vectorDiff(p2->position,p1->position))*vectorNorm(vectorDiff(p2->position,p1->position)))));
    p2->velocity=vectorDiff(p2->velocity, vectorMultByScalar(vectorDiff(p2->position,p1->position),vectorDotProduct(vectorDiff(p2->velocity,p1->velocity),vectorDiff(p2->position,p1->position))*2.0*(p1->mass)/((p1->mass+p2->mass)*vectorNorm(vectorDiff(p2->position,p1->position))*vectorNorm(vectorDiff(p2->position,p1->position)))));
    p1->numCollision++;
    p2->numCollision++;

}

void particleHandleXWallCollision(Particle *p){
    p->velocity.x=-1*(p->velocity.x);
}

void particleHandleYWallCollision(Particle *p){

    p->velocity.y=-1*(p->velocity.y);

}

double partcileGetCollisionTime(Particle *p1, Particle *p2){
    double sigma=p1->radius+p2->radius;
    Vector dV=vectorDiff(p2->velocity, p1->velocity);
    Vector dP=vectorDiff(p2->position, p1->position);
    double d=(vectorDotProduct(dV,dP)*vectorDotProduct(dV,dP))-(vectorDotProduct(dV,dV)*(vectorDotProduct(dP,dP)-(sigma*sigma)));
    if(vectorDotProduct(dV,dP)>=0){
        return INFINITY_TIME;
    }else if(d<0){
        return INFINITY_TIME;
    }
    else{
        return -1*(vectorDotProduct(dV,dP)+sqrt(d))/vectorDotProduct(dV,dV);
    }
}

double particleGetXWallCollisionTime(Particle *p, double width){
    if((p->velocity.x)==0){
        return INFINITY_TIME;
    }else if((p->velocity.x)>0){
        return((p->radius-(p->position.x))/(p->velocity.x));
    }else{
        return((width-(p->radius)-(p->position.x))/(p->velocity.x));
    }
}

double particleGetYWallCollisionTime(Particle *p, double height){
    if((p->velocity.y)==0){
        return INFINITY_TIME;
    }else if((p->velocity.y)>0){
        return((p->radius-(p->position.y))/(p->velocity.y));
    }else{
        return((height-(p->radius)-(p->position.y))/(p->velocity.y));
    }
}

bool particleOverlap(Particle *p1, Particle *p2){
    Vector dP=vectorDiff(p2->position, p1->position);
    if(vectorNorm(dP)<=(p1->radius+p2->radius)){
        return true;
    }else{
        return false;
    }
}

bool particleOutside(Particle *p, double width, double height){
    if((p->position.x+p->radius)>=width || (p->position.x-p->radius)<=0 || (p->position.y+p->radius)>=height || (p->position.y-p->radius)<=0){
        return true;
    }else{
        return false;
    }
}








