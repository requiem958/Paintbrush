/** \file defines.h
 *  \brief Define all symbolic constants and some macros.
 *  \author Marius Monnier
 *  \version 0.1
 */

#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <libconfig.h>

#define SCREEN_HEIGHT   (1024)  /**< Define window height */
#define SCREEN_WIDTH    (1080)  /**< Define window width */

#define STRING_SIZE     (40)    /**< Define maximum size of strings in program */

#define K               *(1000) /**< Define a semi "converting" operator */
#define CTRL_KEYS_NUMBER 4      /**< Define number of control keys for a player */

#define MAX_PLAYERS      (4)      /**< Define maximum number of players */
#define NAME_STRING_MAX  (32)     /**< Define maximum size of player's name */
#define TO_UNDUMMY      (1)       /**< Operator for TODO */

#define NB_IMG_PER_SECOND   (30)  /**< Number of img per second, for the fps manager */

/** \def CLEAR_BUFFER
 *
 *  Little protected macro to clear the buffer after or before a scanf for example
 */
#define CLEAR_BUFFER        do {while(getchar() != '\n');}while(0)

#endif
