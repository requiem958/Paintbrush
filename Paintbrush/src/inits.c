/** \file inits.c
 *  \brief Implement initialisation functions
 *  \author Marius Monnier
 *  \version 0.1
 */

#include "global_types.h"
#include "defines.h"
#include "inits.h"
#include "fonctions.h"

GameData* createGameData(SDL_Window** window, SDL_Renderer** renderer, char *appName)
{
    GameData* data = NULL;
    data = malloc(sizeof(GameData));
    if(data != NULL)
    {
        data->window = window;
        SDL_GetWindowSize(*window, &data->window_width, &data->window_height);
        data->renderer = renderer;

        data->appName = appName;
        data->pixelformat = SDL_AllocFormat(SDL_GetWindowPixelFormat(*window));
        if(data->pixelformat == NULL)
        {
            free(data);
            data = NULL;
        }
        else
        {
            data->display.background = IMG_LoadTexture(*renderer, "background.jpg");
            /*  Create transparent foreground texture */
            SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);
            data->display.foreground = SDL_CreateTexture(*renderer, SDL_GetWindowPixelFormat(*window),
                                        SDL_TEXTUREACCESS_TARGET, data->window_width, data->window_height);
            if(data->display.foreground != NULL)
                clear_texture(data->display.foreground, *renderer);
            /*  Surface Creation */
            data->display.readable_foreground = SDL_CreateRGBSurface(0,
                    data->window_width, data->window_height,
                    data->pixelformat->BitsPerPixel, 0,0,0,0);
            SDL_ConvertSurface(data->display.readable_foreground, data->pixelformat, 0);
            if(data->display.readable_foreground == NULL)
            {
                fprintf(stderr, "Error during surface creation SDL : %s\n", SDL_GetError());
                SDL_DestroyTexture(data->display.background);
                SDL_DestroyTexture(data->display.foreground);
                free(data);
                data = NULL;
            }
            else
                SDL_FillRect(data->display.readable_foreground, NULL, 0);

        }
    }
    else
    {
        data = NULL;
    }
    return data;
}

int initSDLSystems( FPSmanager* manager )
{
    int ret = EXIT_SUCCESS;
    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS )  == -1 || !IMG_Init( IMG_INIT_PNG ) )
    {
        fprintf( stderr, "Initialisation erreur -> %s\n", SDL_GetError() );
        ret = EXIT_FAILURE;
    }
    else
    {
        SDL_LogSetAllPriority( SDL_LOG_PRIORITY_DEBUG );
        SDL_initFramerate( (FPSmanager*) &manager );
        if( manager == NULL )
        {
            fprintf( stderr, "Can't init FPSManager : %s\n", SDL_GetError() );
            ret = EXIT_FAILURE;
        }
        else
        {
            if( SDL_setFramerate( (FPSmanager*) &manager, NB_IMG_PER_SECOND ) == -1 )
            {
                fprintf( stderr, "Can't set framerate to %d : %s\n", NB_IMG_PER_SECOND, SDL_GetError() );
                ret = EXIT_FAILURE;
            }
        }
    }
    return ret;
}

int initWindowAndRenderer( SDL_Window** window, SDL_Renderer** renderer,
                           const unsigned int width, const unsigned int height,
                           const char* title )
{
    int ret = EXIT_SUCCESS;
    *window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE );
    if( *window == NULL )
    {
        ret = EXIT_FAILURE;
        fprintf( stderr, "Can't create window : %s", SDL_GetError() );
    }
    else
    {
        *renderer = SDL_CreateRenderer( *window, -1,
                                        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED |SDL_RENDERER_TARGETTEXTURE );
        if( *renderer == NULL )
        {
            ret = EXIT_FAILURE;
            fprintf( stderr, "Can't create renderer : %s\nWe destroy Window.", SDL_GetError() );
            SDL_DestroyWindow( *window );
        }
        else
        {
            SDL_SetRenderDrawColor( *renderer, 0,0,0,SDL_ALPHA_OPAQUE );
            SDL_RenderClear( *renderer );
            SDL_RenderPresent( *renderer );
        }
    }
    return ret;
}

