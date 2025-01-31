//
//  main.cpp
//  Hakathon_goo
//
//  Created by Matthieu Benoit on 31/01/2025.
//
#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include "Goo.h"
#include "math.h"




int main(int argc, char* argv[]) {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Créer une fenêtre SDL
    SDL_Window* window = SDL_CreateWindow("Goo",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erreur fenêtre: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Créer un renderer SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erreur renderer: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Création du world
    std::vector<Goo> world;
    Goo goo1(450, 200, 1, 1); /* plage de vitesse = [ - 2, +2 ] */
    world.push_back(goo1);
    Goo goo2(350, 200, -1, 1);
    world.push_back(goo2);
    
    bool running = true;
    SDL_Event event;

    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Mise à jour de la position des goos
        for (size_t i = 0; i < world.size(); ++i) {
            world[i].update();
        }

        // Effacer l'écran avec un fond noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
        SDL_RenderClear(renderer);

        // Affichage des Goos
        for (size_t i = 0; i < world.size(); ++i) {
            world[i].render(renderer);
        }

        // Afficher le rendu à l'écran
        SDL_RenderPresent(renderer);

        // Limiter la vitesse de la boucle à environ 60 FPS
        SDL_Delay(30);
    }

    // Libération des ressources et fermeture
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

