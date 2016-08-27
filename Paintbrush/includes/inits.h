/** \file inits.h
 *  \brief Define initialisation prototypes
 *  \author Marius Monnier
 *  \version 0.1
 */

#ifndef INITS_H_INCLUDED
#define INITS_H_INCLUDED

#include "local_types.h"
int initWindowAndRenderer( SDL_Window** window, SDL_Renderer** renderer,
                           const unsigned int width, const unsigned int height, const char* title );
int initSDLSystems( FPSmanager* manager );
GameData *createGameData(SDL_Window** window, SDL_Renderer** renderer, char *appName);

#endif
