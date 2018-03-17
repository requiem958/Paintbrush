/** \file game_fonctions.h
 *  \brief Define the prototypes of core functions
 *  \author Marius Monnier
 *  \version 0.1
 */

#ifndef GAME_FONCTIONS_H_INCLUDED
#define GAME_FONCTIONS_H_INCLUDED

#include "defines.h"

#include "types.h"

#include "fonctions.h"
#include "players.h"

void launch_menu(void);
void launch_game(void);
void launch_replay(void);

int initWindowAndRenderer( SDL_Window** window, SDL_Renderer** renderer,
                           const unsigned int width, const unsigned int height,\
			   const char* title );

int initSDLSystems( FPSmanager* manager );

GameData* createGameData(SDL_Window** window, SDL_Renderer** renderer, \
			 char *appName);

#endif
