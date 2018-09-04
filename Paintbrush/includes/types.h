/** \file types.h
 *  \brief Types needed in program
 *  \author Marius Monnier
 *  \version 0.1
 */

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "defines.h"

#include <SDL2/SDL.h>
#include "SDL2/SDL2_framerate.h"
#include <SDL2/SDL_image.h>
#include <libconfig.h>

/** @defgroup Bases_Types Types de Bases
 * @{
 */

/** \enum Direction
 *  Enumeration of values to define a moving direction.
 *
 */
typedef enum Direction_s
{
    DIR_STOP=0,     /**< When player is stopped (value used in calculus)*/
    DIR_ACTIVE=1,   /**< When player is moving (value used in calculus)*/
    DIR_REVERSE=-1  /**< When player is reverse moving (value used in calculus)*/
} Direction;

/** \enum BrushSize
 *  Enumeration of values related to the size of a Brush, for a painter.
 *
 */
typedef enum BrushSize_s
{
    BRUSH_LITTLE=16,    /**< Size of little painter (malus)*/
    BRUSH_NORMAL=32,    /**< Size of medium painter (normal)*/
    BRUSH_BIG=64        /**< Size of big painter (bonus)*/
} BrushSize;

/** \enum Speed
 * Enumeration of values related to the speed of a painter. (Arbitrary values)
 *
 */
typedef enum Speed_s
{
    SPEED_NULL=0,  /**< The player is stopped */
    SPEED_SLOW=2,   /**< The player has a malus (moving slowly) */
    SPEED_AVERAGE=4,/**< The player is moving normally */
    SPEED_FAST=6    /**< The player is moving fastly, he has a bonus */
} Speed;

/** \enum GameState
 *  Enumeration of the states that the game can have.
 *
 */
typedef enum GameState_s
{
    STATE_QUIT,   /**< The game is stopped, or not still beginning */
    STATE_PAUSED, /**< Pause mode of the game */
    STATE_PLAYING,/**< Players are gaming */
    STATE_CONFIGURATION /**< We are in configuration steps */

} GameState;

/** \enum ControlKeys
 *  Indexes used for the ControlKeys tabs.
 *
 */
typedef enum ControlKeys_s
{
    CTRL_KEY_RIGHT=0,   /**< ID of RIGHT_KEY */
    CTRL_KEY_LEFT=1,    /**< ID of LEFT_KEY */
    CTRL_KEY_UP=2,      /**< ID of UP_KEY */
    CTRL_KEY_DOWN=3     /**< ID of DOWN_KEY */
} ControlKeys;

/** \struct DirectionVector
 *
 *  The two directions that a player can have.
 */
typedef struct DirectionVector_s
{
    Direction x;    /**< Direction on X-axis */
    Direction y;    /**< Direction on Y-axis */
} DirectionVector;

/** \struct SpeedVector
 *
 *  Speeds of a player, related to malus and bonus
 */
typedef struct SpeedVector_s
{
    Speed x;    /**< Speed on X-axis */
    Speed y;    /**< Speed on Y-axis */
} SpeedVector;

/** \struct Screen
 *
 *  Define the screen of the game
 *  \todo Add the GUI zone
 */
typedef struct Screen_s
{
    SDL_Texture *background; /**< Background, a picture or a sample color */
    SDL_Texture *foreground; /**< Layer where paint lines will be displayed */
    SDL_Surface *readable_foreground; /**< Surface used for pixel manipulating */
} Screen;

/** @} Fin des types de bases*/

/** @defgroup Composed_Types Types composites
 *@{
 */

/** \struct GameData
 *
 *  All data that the game must have to be ready
 */
typedef struct GameData_s
{
    config_t configFile;   /**< \b Unused \b nowadays, but the data will be readable */
    char *appName;  /**< \b Unused \b nowadays, will define the name of the window and app */
    GameState current_state;    /**< Used for launch functions */
    SDL_PixelFormat *pixelformat;   /**< Pixel format of the screen */
    SDL_Window **window;    /**< Pointer to the main window */
    int window_width;       /**< Window width in pixels */
    int window_height;      /**< Window height in pixels */
    unsigned int numberOfPlayer;    /**< Number of players that plays */
    SDL_Renderer **renderer;        /**< Pointer to the renderer */
    FPSmanager **manager;           /**< Pointer to the FPS manager of the game */
    Screen display;                 /**< Screen structure to displaying */
}GameData;

/** \struct Player
 *  \brief Structure of a Player.
 */
typedef struct player_s
{
  SDL_Texture* spriteRight;   /**< The sprite when the player is moving to the right */
  SDL_Texture* spriteLeft;    /**< The sprite when the player is moving to the left */
  SDL_Texture** activeSprite;  /**< The sprite that is actually used */

  /** \var SDL_Rect position
   *  \brief Position and size
   *
   *  Actually, the \b x and \b y members of the SDL_Rect struct are used for position
   *  and the \b h and \b w members of the SDL_Rect struct are equals to brushSize
   */
  SDL_Rect position;
  SDL_Keycode keys[CTRL_KEYS_NUMBER]; /**< The control keys to move the player */

  BrushSize size; /**< Size of the brush*/


  Uint32 color; /**< Coded RGB color */
  SDL_Color struct_color; /**< Detailled RGBA color*/

  
  SDL_bool isdef;         /**< indicator of player existence */
  char name[NAME_STRING_MAX]; /**< String of NAME_STRING_MAX chars to store the player name */
  char id;    /**< Identification number of the player (0 to MAX_PLAYERS) */
  double scoreP;
  
  /**< Score of the player.
   *
   * \todo Why double ? Long int isn't sufficient ?
   */
  SpeedVector speed; /**< The speed of the player*/

  DirectionVector dir;
  /**< The direction of the player (8 possibility)
   * \todo Make the direction totally vectorial on a circle
   */
}Player;

/** @} */

#endif
