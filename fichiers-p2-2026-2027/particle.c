#include <stdlib.h>
#include <stdio.h>
#include "particle.h"
#include "vector.h"
#include "color.h"
#include "math.h"
#include "event.h"

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
    Vector dp = vectorDiff(p2->position, p1->position);
    Vector dv = vectorDiff(p2->velocity, p1->velocity);
    double dist2 = vectorDotProduct(dp, dp);
    double distance = sqrt(dist2);
    double minDistance = p1->radius + p2->radius;

    if (distance > 0 && distance < minDistance)
    {
        Vector correction = vectorMultByScalar(
            dp, (minDistance - distance) / distance);
        p1->position = vectorDiff(
            p1->position,
            vectorMultByScalar(correction, p2->mass / (p1->mass + p2->mass)));
        p2->position = vectorSum(
            p2->position,
            vectorMultByScalar(correction, p1->mass / (p1->mass + p2->mass)));
        dp = vectorDiff(p2->position, p1->position);
        dist2 = vectorDotProduct(dp, dp);
    }

    double impulse = vectorDotProduct(dv, dp) * 2.0 / ((p1->mass + p2->mass) * dist2);
    Vector v1 = p1->velocity;
    Vector v2 = p2->velocity;

    p1->velocity = vectorSum(v1, vectorMultByScalar(dp, impulse * p2->mass));
    p2->velocity = vectorDiff(v2, vectorMultByScalar(dp, impulse * p1->mass));
    p1->numCollision++;
    p2->numCollision++;
}

void particleHandleXWallCollision(Particle *p){
    p->velocity.x=-1*(p->velocity.x);
}

void particleHandleYWallCollision(Particle *p){

    p->velocity.y=-1*(p->velocity.y);

}

//Verif en cours

double particleGetCollisionTime(Particle *p1, Particle *p2){
    double sigma=p1->radius+p2->radius;
    Vector dV=vectorDiff(p2->velocity, p1->velocity);
    Vector dP=vectorDiff(p2->position, p1->position);
    double dpdv = vectorDotProduct(dV, dP);
    double dv2 = vectorDotProduct(dV, dV);
    double distance2 = vectorDotProduct(dP, dP);
    double d=(dpdv * dpdv) - (dv2 * (distance2 - sigma * sigma));
    if (distance2 <= sigma * sigma && dpdv < 0)
    {
        return 0;
    }
    if (dpdv >= 0 || dv2 == 0){
        return INFINITY_TIME;
    }else if(d<0){
        return INFINITY_TIME;
    }
    else{
        //printf("Croisement dans: %f \n",(-1*(vectorDotProduct(dV,dP)+sqrt(d))/vectorDotProduct(dV,dV)));
        //printf("Croisement dans: %f \n",-1*(vectorDotProduct(dV,dP)+sqrt(d)));

        return ((-dpdv - sqrt(d)) / dv2);
    }
}


//OK
double particleGetXWallCollisionTime(Particle *p, double width){
    if((p->velocity.x)==0){
        return INFINITY_TIME;
    }else if((p->velocity.x)<0){
        double time = (p->radius - p->position.x) / p->velocity.x;
        return time < 0 ? 0 : time;
    }else{
        double time = (width - p->radius - p->position.x) / p->velocity.x;
        return time < 0 ? 0 : time;
    }
}

//OK
double particleGetYWallCollisionTime(Particle *p, double height){
    if((p->velocity.y)==0){
        return INFINITY_TIME;
    }else if((p->velocity.y)<0){
        //printf("temps: %f\n",((p->radius-(p->position.y))/(p->velocity.y)));
        double time = (p->radius - p->position.y) / p->velocity.y;
        return time < 0 ? 0 : time;
    }else{
        double time = (height - p->radius - p->position.y) / p->velocity.y;
        return time < 0 ? 0 : time;
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
