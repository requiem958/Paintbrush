/** \file fonctions.h
 *  \brief Define prototypes of common functions
 *          and includes other Headers files.
 *  \author Marius Monnier
 *  \version 0.1
 */
#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include "global_types.h"

Uint32 getPixel( SDL_Surface* surface, int x, int y );
void str_replace(char **s, int token, int replacement);
int readline(char *s, int n);
void dummy();
void clear_texture(SDL_Texture *texture, SDL_Renderer *renderer);
int setRenderDrawColor(SDL_Renderer* renderer, SDL_Color *color);

#endif
