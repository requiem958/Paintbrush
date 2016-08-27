/** \file painters.h
 *  \brief Define all functions designed to manipulate
            player and painter object.
 *  \author Marius Monnier
 *  \version 0.1
 */

#ifndef PAINTERS_H_INCLUDED
#define PAINTERS_H_INCLUDED

#include "includes/SDL2/SDL.h"
#include "painters_types.h"

/* Functions for painters and players*/

painter_ptr createSkeletonPainter();
int deletePainter(painter_ptr p );
void movePainter(painter_ptr p  );

void setDirectionX(painter_ptr p, const Direction dx );
void setDirectionY(painter_ptr p, const Direction dy );
void setDirection( painter_ptr p, const Direction dx, const Direction dy);
void setSpeed( painter_ptr p, const Speed speedx, const Speed speedy);

void setColor(painter_ptr p, const Uint32 c );
void setBrushSize(painter_ptr p, const BrushSize size);
void setPosition(painter_ptr p, const int x, const int y  );
void setScore(Player_ptr p, double score);
void setCtrlKeys(painter_ptr p,
                const SDL_Keycode key_right,
                const SDL_Keycode key_left,
                const SDL_Keycode key_up,
                const SDL_Keycode key_bottom);
#endif
