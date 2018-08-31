/** \file players.h
 *  \brief Define players related functions prototypes
 *  \author Marius Monnier
 *  \version 0.1
 */

#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

#include "defines.h"
#include "fonctions.h"
#include "types.h"

player* createPlayer();

void setSpriteRight(player*,SDL_Texture*);
void setSpriteLeft(player*,SDL_Texture*);
void setActiveSprite(player*,SDL_Texture**);
void setPosition(player*,const int, const int);
void setBrushSize(player*,const BrushSize);
void setCtrl(player*,const int,const SDL_Keycode);
void setCodedColor(player*,const Uint32);
void setStructColor(player*,const Uint8 ,const Uint8 ,const Uint8 , const Uint8 );

void setDef(player*,const SDL_bool);
void setName(player*,const char*,const unsigned int);
void setId(player*,const char);
void setScore(player*,const double);
void setSpeedX(player*,const Speed);
void setSpeedY(player*,const Speed);
void setSpeed(player*,const Speed,const Speed);
void setDirectionX(player*,const Direction);
void setDirectionY(player*,const Direction);
void setDirection(player*,const Direction,const Direction);

SDL_Texture* getSpriteRight(const player*);
SDL_Texture* getSpriteLeft(const player*);
SDL_Texture* getActiveSprite(const player*);
int getX(const player*);
int getY(const player*);
SDL_Keycode getCtrlRight(const player*);
SDL_Keycode getCtrlLeft(const player*);
SDL_Keycode getCtrlDown(const player*);
SDL_Keycode getCtrlUp(const player*);
Uint32 getCodedColor(const player*);
SDL_Color getStructColor(const player*);

SDL_bool isDef(const player*);
char* getName(const player*);
char getId(const player*);
double getScore(const player*);
Speed getXSpeed(const player*);
Speed getYSpeed(const player*);
Direction getXDir(const player*);
Direction getYDir(const player*);

void movePlayer(player*);
int deletePlayer(player* play);
int deleteAllPlayers();

#endif
