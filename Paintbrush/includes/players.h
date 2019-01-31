/** \file Players.h
 *  \brief Define Players related functions prototypes
 *  \author Marius Monnier
 *  \version 0.1
 */

#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

#include "defines.h"
#include "fonctions.h"
#include "types.h"

Player* createPlayer();

void setSpriteRight(Player*,SDL_Texture*);
void setSpriteLeft(Player*,SDL_Texture*);
void setActiveSprite(Player*,SDL_Texture**);
void setPosition(Player*,const int, const int);
void setBrushSize(Player*,const BrushSize);
void setCtrl(Player*,const int,const SDL_Keycode);
void setCodedColor(Player*,const Uint32);
void setStructColor(Player*,const Uint8 ,const Uint8 ,const Uint8 , const Uint8 );

void setDef(Player*,const SDL_bool);
void setName(Player*,const char*,const unsigned int);
void setId(Player*,const char);
void setScore(Player*,const double);
void setSpeedX(Player*,const Speed);
void setSpeedY(Player*,const Speed);
void setSpeed(Player*,const Speed,const Speed);
void setDirectionX(Player*,const Direction);
void setDirectionY(Player*,const Direction);
void setDirection(Player*,const Direction,const Direction);

SDL_Texture* getSpriteRight(const Player*);
SDL_Texture* getSpriteLeft(const Player*);
SDL_Texture* getActiveSprite(const Player*);
int getX(const Player*);
int getY(const Player*);
SDL_Keycode getCtrlRight(const Player*);
SDL_Keycode getCtrlLeft(const Player*);
SDL_Keycode getCtrlDown(const Player*);
SDL_Keycode getCtrlUp(const Player*);
Uint32 getCodedColor(const Player*);
SDL_Color getStructColor(const Player*);

SDL_bool isDef(const Player*);
char* getName(const Player*);
char getId(const Player*);
double getScore(const Player*);
Speed getXSpeed(const Player*);
Speed getYSpeed(const Player*);
Direction getXDir(const Player*);
Direction getYDir(const Player*);

void movePlayer(Player*);
int deletePlayer(Player* play);
int deleteAllPlayers();

#endif
