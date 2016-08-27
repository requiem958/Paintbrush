/** \file painters_types.h
 *  \brief Define the two structures Painter and Player
 *          and their pointers.
 *  \author Marius Monnier
 *  \version 0.1
 */

#ifndef PAINTERS_TYPES_H_INCLUDED
#define PAINTERS_TYPES_H_INCLUDED

#include "includes/SDL2/SDL.h"
#include "local_types.h"
#include "defines.h"
/** \struct painter
 *  \brief Structure of a painter used everywhere.
 */
typedef struct _painter
{
    SDL_Texture* spriteRight;   /**< The sprite when the painter is moving to the right */
    SDL_Texture* spriteLeft;    /**< The sprite when the painter is moving to the left */
    SDL_Texture** activeSprit;  /**< The sprite that is actually used */

    /** \var SDL_Rect position
     *  \brief The position and size of the player
     *
     *  Actually, the \b x and \b y members of the SDL_Rect struct are used for position
     *  and the \b h and \b w members of the SDL_Rect struct are equals to brushSize
     */
    SDL_Rect position;
    SDL_Keycode keys[CTRL_KEYS_NUMBER]; /**< The control keys to move the painter */

    int brushSize; /**< Size of the brush of the painter*/
    SpeedVector speed; /**< The speed of the painter*/
    DirectionVector dir;
    /**< The direction of the painter (8 possibility)
     * \todo Make the direction totally vectorial on a circle
     */

    Uint32 color; /**< Coded RGB color of the painter */
    SDL_Color struct_color; /**< Detailled RGBA color of the painter*/

} painter;

typedef painter * painter_ptr; /**< Pointer to painter */

/** \struct Player
 *  \brief Structure of a Player.
 */
typedef struct _player
{
    painter_ptr Painter;    /**< pointer to the painter of the Player */
    SDL_bool isdef;         /**< indicator of player existence */
    char name[NAME_STRING_MAX]; /**< String of NAME_STRING_MAX chars to store the player name */
    char id;    /**< Identification number of the player (1-2-3 or 4) */
    double scoreP;
    /**< Score of the player.
     *
     * \todo Why double ? Long int isn't sufficient ?
     */
}Player;

typedef Player * Player_ptr; /**< Pointer to Player */


#endif
