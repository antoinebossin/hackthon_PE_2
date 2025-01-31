//
//  Goo.h
//  Hakathon_goo
//
//  Created by Matthieu Benoit on 31/01/2025.
//
#include <SDL2/SDL.h>
#include <iostream>
#include <random>

#ifndef GOO_H
#define GOO_H


const int windowWidth = 800;
const int windowHeight = 600;

float distance_max=400;
float distance_min=10;

class Goo {
public:
    float x, y;  // Position
    float vx, vy; // Vitesse

    float d_min = 100;
    float m=0.4;
    float g=9.81/20;
    float k=0.001;

    std::vector<Goo*> neighbors;
    std::vector<float> l0;


    float distance(Goo* A) {
        std::cout<<sqrt(std::pow((x-(*A).x),2)+std::pow((y-(*A).y),2))<<std::endl;
        return sqrt(std::pow((x-(*A).x),2)+std::pow((y-(*A).y),2));
    }

    Goo(float x, float y, float vx, float vy) : x(x), y(y), vx(vx), vy(vy) {}

    void update() {
        float dt=1;
        x=x+vx*dt;
        y=y+vy*dt;

        float force_x=0;
        float force_y=g;
        for (int i=0;i<neighbors.size();i++) {
            Goo* A=neighbors[i];
            //float theta=std::atan((A.y-y)/(A.x-x));
            float l_0=l0[i];
            //if (A.x<x) {theta=theta+3.14159;}
            if (distance(A)<distance_max and distance(A)>distance_min) {
                force_x=force_x+k/m*(distance(A)-l_0)*((*A).x-x)/distance(A);
                force_y=force_y+k/m*(distance(A)-l_0)*((*A).y-y)/distance(A);
            }
            else if (distance(A)<distance_min) {
                force_x=force_x+k/m*(distance(A)-l_0)*((*A).x-x)/distance_min;
                force_y=force_y+k/m*(distance(A)-l_0)*((*A).y-y)/distance_min;
            }
        }
        vx=vx+force_x*dt;
        vy=vy+force_y*dt;
        // Rebondir sur les bords
        if (x < 0 || x > windowWidth) {
            vx = -vx; // Inverser la vitesse horizontale
        }
        if (y < 0 || y > windowHeight) {
            vy = -vy + g ; // Inverser la vitesse verticale
        }
    }

    // Affiche le Goo à l'écran
    void render(SDL_Renderer* renderer) {
        SDL_Rect GooRect = {static_cast<int>(x), static_cast<int>(y), 10, 10}; // Le Goo est un carré de 10x10
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur blanche
        SDL_RenderFillRect(renderer, &GooRect);
    }
};
#endif

