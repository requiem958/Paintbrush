/** \file players.c
 *  \brief Implement public and static players related functions
 *  \author Marius Monnier
 *  \version 0.1
 */

#include "defines.h"
#include "fonctions.h"
#include "players.h"
#include "painters.h"

extern GameData* data;
extern Player* players[];
static Player* allocPlayer();
static int initPlayer(Player* player);

/** \fn Player* createPlayer()
 *  \brief Function that create a player in interaction with user
 *  \return A pointer to the created player if success, NULL otherwise.
 *
 *  \todo Change the way to preconfigured players.
 */
Player* createPlayer()
{
    static unsigned char actual_id = 0;
    Player* player = NULL;
    SDL_Color* color = NULL;

    if( (player = allocPlayer()) != NULL)
    {
        if (initPlayer(player) != EXIT_FAILURE)
        {
        player->id = actual_id;
        color = &(player->Painter->struct_color);
        printf( "Please enter a name for that young player (31 letters max):" );
        readline( player->name, NAME_STRING_MAX );
        printf( "Now type the three (r,g,b) components of his color :" );
        scanf( "%3u %3u %3u", &color->r,&color->g,&color->b );
        CLEAR_BUFFER;
        if  ( color->r + color->g + color->b <= ( UINT8_MAX*3 ))
        {
            if( data->pixelformat != NULL )
            {
                color->a = SDL_ALPHA_OPAQUE;
                setColor(player->Painter,SDL_MapRGB(data->pixelformat,color->r,color->g,color->b));
                setBrushSize(player->Painter, BRUSH_NORMAL);
                setSpeed(player->Painter, SPEED_AVERAGE, SPEED_AVERAGE);
                setDirection(player->Painter, DIR_STOP, DIR_STOP);
                setScore(player, 0);

                switch(player->id)
                {
                    case 0:
                        setPosition(player->Painter,    (data->window_width/4),
                                                        (data->window_height/4) );
                        setCtrlKeys(player->Painter, SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN);
                        break;
                    case 1:
                        setPosition(player->Painter,    3*(data->window_width/4),
                                                        (data->window_height/4) );
                        setCtrlKeys(player->Painter, SDLK_d, SDLK_q ,SDLK_z ,SDLK_s);
                        break;
                    case 2:
                        setPosition(player->Painter,    (data->window_width/4),
                                                        (data->window_height/4) );
                        setCtrlKeys(player->Painter, SDLK_m, SDLK_k, SDLK_o, SDLK_l);
                        break;
                    case 3:
                        setPosition(player->Painter,    3*(data->window_width/4),
                                                        3*(data->window_height/4) );
                        setCtrlKeys(player->Painter, SDLK_6, SDLK_4, SDLK_8, SDLK_5);
                        break;
                    default:
                        SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                                    "Actual id is invalid : %d", actual_id);
                        setPosition(player->Painter, 42,42);
                        setCtrlKeys(player->Painter, SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN);
                        break;

                }

                player->Painter->spriteLeft = IMG_LoadTexture( *data->renderer,
                                              "paintbrush_toleft.png" );
                player->Painter->spriteRight = IMG_LoadTexture( *data->renderer,
                                               "paintbrush_toright.png" );
                SDL_QueryTexture( player->Painter->spriteLeft, NULL, NULL,
                                  &( player->Painter->position.w ), &( player->Painter->position.h ) );
                player->Painter->activeSprit = &player->Painter->spriteLeft;
            }
        }
    }
    }
    /* Creation Phase end  */
    actual_id = (actual_id != data->numberOfPlayer) ? (actual_id + 1) : (0);
    return player;
}

static Player* allocPlayer()
{
    Player* temp;
    temp = malloc(sizeof(Player));
    if(temp == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Memory error");
    return temp;
}

static int initPlayer(Player* player)
{
    int ret = EXIT_SUCCESS;

    if(player == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Player isn't allocated");
        ret = EXIT_FAILURE;
    }
    else if( player->isdef == SDL_TRUE )
    {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,
                      "Player %s is almost allocated, will ignore it", player->name );
    }
    else
    {
        player->isdef = SDL_TRUE;
        player->scoreP = 0.0;

        player->Painter = createSkeletonPainter();
        if(player->Painter == NULL)
        {
            deletePlayer(player);
            ret = EXIT_FAILURE;
        }
    }
    return ret;
}

int deletePlayer( Player_ptr play )
{
    int ret = EXIT_SUCCESS;
    if( play != NULL)
    {
        if( play->isdef == SDL_TRUE )
        {
            if( play->Painter != NULL )
            {
                deletePainter( play->Painter );
                play->scoreP = 0;
                play->isdef = SDL_FALSE;
            }
            else
            {
                SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                             "Sub Painter of player (%s) isn't allocated, it's not normally.", play->name );
                play->isdef = SDL_FALSE;
                free(play);
                ret = EXIT_FAILURE;
            }
        }
        else
        {
            SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                         "Player isn't defined, he's probably not still created or some errors happened" );
            ret = EXIT_FAILURE;
            free(play);
        }
    }
    else
    {
        SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                        "Player is not allocated");
        ret = EXIT_FAILURE;
    }
    return ret;
}

int deleteAllPlayers()
{
    int ret = EXIT_SUCCESS;
    while( data->numberOfPlayer-- >0 )
    {
        if( players[data->numberOfPlayer]->isdef
                && players[data->numberOfPlayer]->Painter != NULL )
        {
            if( deletePlayer( players[data->numberOfPlayer] ) != EXIT_SUCCESS )
            {
                SDL_LogError( SDL_LOG_CATEGORY_ERROR,
                              "During player deleting (see above)" );
                ret = EXIT_FAILURE;
            }
        }
    }

    return ret;
}
