#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 555

#define TILE_SIZE 16
#define BG_COLOR_CODE 0, 0, 0, 255

#define SCREEN_TITLE "Calculator"

void drawImage(SDL_Rect* destRect, int x, int y, int w, int h) {
    destRect->x = x;
    destRect->y = y;
    destRect->w = w;
    destRect->h = h;
}

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error: SDL failed to initialize SDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Error: Failed to open window SDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Error: Failed to initialize SDL_image SDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Error: Failed to create renderer SDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    SDL_Surface* imageSurface = IMG_Load("../assets/calc.png");
    if (!imageSurface) {
        std::cout << "Error: Failed to load image SDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (!texture) {
        std::cout << "Error: Failed to create texture SDL Error: '" << SDL_GetError() << "'\n";
        return 1;
    }

    SDL_Rect destRect;
    drawImage(&destRect, 0, 0, imageSurface->w, imageSurface->h);

    SDL_FreeSurface(imageSurface);

    bool running = true;
    std::cout << "Calculator Started!\n"; 
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, BG_COLOR_CODE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_RenderPresent(renderer);
    }
    std::cout << "Calculator Stopped!\n";

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}