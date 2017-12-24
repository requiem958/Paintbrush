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
void setDirectionX(player*,const Direction);
void setDirectionY(player*,const Direction);
void setDirection(player*,const Direction,const Direction);
void movePlayer(player*);
int deletePlayer(player* play);
int deleteAllPlayers();

#endif
