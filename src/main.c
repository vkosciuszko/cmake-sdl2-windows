#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    printf("Hello CMake");

    return 0;
}
