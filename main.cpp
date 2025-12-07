#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define MAX 1024

// Skip comment lines (# ...)
void skipComments(FILE *fp, char *buffer) {
    do {
        if (!fgets(buffer, MAX, fp)) return;
    } while (buffer[0] == '#');
}

int main(int argc, char *argv[]) 
{
    FILE *fp = fopen("image.ppm", "rb");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    char buffer[MAX];

    // --- 1. Read the magic number: P6 ---
    fgets(buffer, MAX, fp);
    if (buffer[0] != 'P' || buffer[1] != '6') {
        printf("Error: Not a P6 PPM file!\n");
        return 1;
    }

    // --- 2. Read width and height (skip comments) ---
    skipComments(fp, buffer);
    int width, height;
    sscanf(buffer, "%d %d", &width, &height);

    // --- 3. Read max color (skip comments) ---
    skipComments(fp, buffer);
    int maxval;
    sscanf(buffer, "%d", &maxval);

    // --- 4. IMPORTANT: consume the newline after maxval ---
    // fgetc(fp);

    // --- 5. Initialize SDL ---
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "PPM Viewer (P6)", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        0
    );

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    if (!surface) {
        printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // --- 6. Read RGB pixels and draw ---
    Uint32 color;
    SDL_Rect pixel = {0, 0, 1, 1};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            Uint8 r = fgetc(fp);
            Uint8 g = fgetc(fp);
            Uint8 b = fgetc(fp);

            color = SDL_MapRGB(surface->format, r, g, b);

            pixel.x = x;
            pixel.y = y;

            SDL_FillRect(surface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(window);

    fclose(fp);

    // --- 7. Event loop ---
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
