#include "particle.h"
#include "simulator.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
    int particleNumber=1000;
    int width=200;
    int height=200;
    double particleMass=1.0;
    double particleRadius=1.0;
    double particleSpeed=1.0;
    double numbColl=200.0;
    double dt=1.0;
    Color particleColor=COLOR_BLUE;
    bool added=false;
    Simulator *s=simulatorCreate(width, height, particleNumber);
    srand(time(NULL));

    for (int i=0;i<particleNumber;i++){
        while(added==false){
            Vector particleVelocity;
            particleVelocity.x=rand();
            particleVelocity.y=rand();
            particleVelocity=vectorMultByScalar(particleVelocity,(particleSpeed/vectorNorm(particleVelocity)));


            Vector particlePosition;
            particlePosition.x=((rand()%(width-1))+1);
            particlePosition.y=((rand()%(height-1))+1);
            Particle *p=particleCreate(particleRadius,particleMass,particlePosition,particleVelocity,particleColor);
            added=simulatorAddParticle(s,p);
        }
        added=false;
        printf("Particule %d ajoutée\n",i+1);

    }
    while(simulatorStatParticles(s, particleGetNumCollisions)<numbColl){
        simulatorStep(s,dt);
        printf("Nombre moyen de collision: %.2f\n",simulatorStatParticles(s, particleGetNumCollisions));
    }
    FILE *fichier = fopen("results/particlesVelocity.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    for (int i=0;i<particleNumber;i++){
        double speedNorm=vectorNorm(particleGetVelocity(simulatorGetParticle(s,i)));
        fprintf(fichier,"%.2f\n",speedNorm);
    }
    fclose(fichier);

    double eCinMean=simulatorStatParticles(s, particleKineticEnergy);
    printf("L'énergie cinétique moyenne est: %f\n",eCinMean);
    return 0;



}