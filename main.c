#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define MAX 1000

int main(int argc, char *argv[])
// int main()
{
    FILE *in = fopen("image.ppm", "rb");
    if (!in)
    {
        printf("Error opening file!\n");
        return 1;
    }
    char *pthroway = (char *)calloc(MAX, sizeof(char));
    // read first line (specifier for p3 or p6)
    fgets(pthroway, MAX, in);
    // read second line (commnets)
    fgets(pthroway, MAX, in);
    // read third line (dimensions :- width and height)

    char *pdimensions = (char *)calloc(MAX, sizeof(char));
    fgets(pdimensions, MAX, in);

    // read fourth line (max color value--ignore it)
    fgets(pthroway, MAX, in);
    free(pthroway);

    // initialized the width and height
    int width = -1;
    int height = -1;
    sscanf(pdimensions, "%d %d\n", &width, &height);
    free(pdimensions);
    
    printf("width = %d, height = %d\n", width, height);
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    Uint32 color;

    SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)

        {
            Uint8 r, g, b;
            r = fgetc(in);
            g = fgetc(in);
            b = fgetc(in);

            color = SDL_MapRGB(psurface->format, r, g, b);

            pixel.x = x;
            pixel.y = y;
            SDL_FillRect(psurface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(pwindow);

    fclose(in);

    int app_running = 1;
    SDL_Event event;
    while (app_running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                app_running = 0;
            }
        }
        SDL_Delay(10);
    }

    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}
