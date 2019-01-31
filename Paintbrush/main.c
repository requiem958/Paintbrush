#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char ** argv)
{
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );
    IMG_Init(IMG_INIT_PNG);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
