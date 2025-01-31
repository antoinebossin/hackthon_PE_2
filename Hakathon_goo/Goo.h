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

class Goo {
public:
    float x, y;  // Position
    float vx, vy; // Vitesse

    Goo(float x, float y, float vx, float vy) : x(x), y(y), vx(vx), vy(vy) {}

    // Met à jour la position du Goo
    void update() {
        x += vx;
        y += vy;

        // Rebondir sur les bords
        if (x < 0 || x > windowWidth) {
            vx = -vx; // Inverser la vitesse horizontale
        }
        if (y < 0 || y > windowHeight) {
            vy = -vy; // Inverser la vitesse verticale
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

