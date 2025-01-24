// Normal C++ program to draw shapes using SDL2
// Random shapes and colors


#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <time.h>
#include <math.h>

// Draw a circle outline
void DrawCircle(SDL_Renderer* renderer, int32_t n_cx, int32_t n_cy, int32_t radius) {
    const int32_t diameter = (radius * 2);

    int32_t n_x = (radius - 1);
    int32_t n_y = 0;
    int32_t n_tx = 1;
    int32_t n_ty = 1;
    int32_t n_error = (n_tx - diameter);

    while (n_x >= n_y) {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, n_cx + n_x, n_cy - n_y);
        SDL_RenderDrawPoint(renderer, n_cx + n_x, n_cy + n_y);
        SDL_RenderDrawPoint(renderer, n_cx - n_x, n_cy - n_y);
        SDL_RenderDrawPoint(renderer, n_cx - n_x, n_cy + n_y);
        SDL_RenderDrawPoint(renderer, n_cx + n_y, n_cy - n_x);
        SDL_RenderDrawPoint(renderer, n_cx + n_y, n_cy + n_x);
        SDL_RenderDrawPoint(renderer, n_cx - n_y, n_cy - n_x);
        SDL_RenderDrawPoint(renderer, n_cx - n_y, n_cy + n_x);

        if (n_error <= 0) {
            ++n_y;
            n_error += n_ty;
            n_ty += 2;
        }

        if (n_error > 0) {
            --n_x;
            n_tx += 2;
            n_error += (n_tx - diameter);
        }
    }
}

// Draw a filled circle
void FillCircle(SDL_Renderer* renderer, int32_t cx, int32_t cy, int32_t radius) {
    for (int32_t y = -radius; y <= radius; y++) {
        for (int32_t x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

// Draw a polygon outline
void DrawPolygon(SDL_Renderer* renderer, int32_t n, int32_t cx, int32_t cy, int32_t radius) {
    if (n < 3) return;

    float angle = 2 * M_PI / n;

    for (int32_t i = 0; i < n; i++) {
        // Draw the polygon
        SDL_RenderDrawLine(renderer,
                           cx + radius * cos(i * angle),
                           cy + radius * sin(i * angle),
                           cx + radius * cos((i + 1) * angle),
                           cy + radius * sin((i + 1) * angle));
    }
}

// Draw a filled polygon
void FillPolygon(SDL_Renderer* renderer, int32_t n, int32_t cx, int32_t cy, int32_t radius) {
    if (n < 3) return;

    float angle = 2 * M_PI / n;

    for (int32_t i = 0; i < n; i++) {
        // Draw the polygon
        SDL_RenderDrawLine(renderer,
                           cx,
                           cy,
                           cx + radius * cos(i * angle),
                           cy + radius * sin(i * angle));
    }
}





int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create SDL Window
    SDL_Window* window = SDL_CreateWindow("SDL Shape Drawing", 5, 30, 900, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create SDL Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop flag
    bool running = true;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // initialize random seed
        srand(time(NULL));

        // Generate random numbers
        int R = rand() % 256;
        int G = rand() % 256;
        int B = rand() % 256;
        int opacity = rand() % 256;

        // std::cout << "R: " << R << " G: " << G << " B: " << B << " opacity: " << opacity << std::endl;

        // set draw color
        SDL_SetRenderDrawColor(renderer, R, G, B, opacity);
        SDL_RenderDrawPoint(renderer, R, G);

        // Draw a point
        SDL_SetRenderDrawColor(renderer,R, G, B, opacity); // Random color
        SDL_RenderDrawPoint(renderer, R, G); // Random point

        // Draw a line
        SDL_SetRenderDrawColor(renderer, R, G, B, opacity); // Random color
        SDL_RenderDrawLine(renderer, R,G, B, opacity); // Random line

        // Draw a circle
        SDL_SetRenderDrawColor(renderer, R, G, B, opacity); // Random color
        DrawCircle(renderer, R, G, B); // Random circle

        // Draw a filled circle
        SDL_SetRenderDrawColor(renderer, R, G, B, opacity); // Random color
        FillCircle(renderer, R, G, B); // Random filled circle

        // Draw a polygon
        SDL_SetRenderDrawColor(renderer, R, G, B, opacity); // Random color
        DrawPolygon(renderer, R, G, B, opacity); // Random polygon

        // Draw a filled polygon
        SDL_SetRenderDrawColor(renderer, R, G, B, opacity); // Random color
        FillPolygon(renderer, R, G, B, opacity); // Random filled polygon


        // Draw a rectangle outline
        SDL_SetRenderDrawColor(renderer, R, G, B, opacity); // Random color
        SDL_Rect rect = {R, G, B, opacity};
        SDL_RenderDrawRect(renderer, &rect);

        // Draw a filled rectangle
        SDL_SetRenderDrawColor(renderer, R, G, B, opacity); // Random color
        SDL_Rect filledRect = {R, G, B, opacity};
        SDL_RenderFillRect(renderer, &filledRect);

        // Present the shapes on the screen
        SDL_RenderPresent(renderer);


        // Delay to slow things down
        SDL_Delay(10);

    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
