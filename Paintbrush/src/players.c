/** \file players.c
 *  \brief Implement public players related functions and static painters related functions
 *  \author Marius Monnier
 *  \version 0.1
 */


#include "players.h"


extern GameData* data;
extern player* players[];


static painter* allocPainter( void )
{
    painter* testing = NULL;
    testing = malloc( sizeof( painter ) );
    return testing;
}

static void initPainter(painter* paint)
{
    if(paint != NULL)
    {
        paint->activeSprit = NULL;
        paint->brushSize = BRUSH_NORMAL;
        paint->position.h =0;
        paint->position.w =0;
        paint->position.x =0;
        paint->position.y =0;
    }
}

static painter* createSkeletonPainter()
{
    painter* paint = NULL;

    paint = allocPainter();
    if(paint != NULL)
        initPainter(paint);
    else
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Memory error (painter alloc)");
    return paint;
}

static void setColor( painter* p, const Uint32 c )
{
    if(p != NULL)
    {
        p->color = c;
    }
}


static void setBrushSize(painter* p, const BrushSize size)
{
    if(p != NULL)
    {
        p->brushSize = size;
    }
}

static void setPosition( painter* p, const int x, const int y )
{
    if( p != NULL )
    {
        if(x != -1)
            p->position.x = x;
        if(y != -1)
            p->position.y = y;
    }
}

static void setCtrlKeys(painter* p,
                const SDL_Keycode key_right, const SDL_Keycode key_left,
                const SDL_Keycode key_up, const SDL_Keycode key_bottom)
{
    if(p != NULL)
    {
        p->keys[CTRL_KEY_RIGHT] = key_right;
        p->keys[CTRL_KEY_LEFT]  = key_left;
        p->keys[CTRL_KEY_DOWN]  = key_bottom;
        p->keys[CTRL_KEY_UP]    = key_up;
    }
}

static int deletePainter( painter* p )
{
    if( p != NULL )
    {
      /** \todo Use native painter functions */
        p->activeSprit  = NULL;
        p->position.h =0;
        p->position.w =0;
        p->position.x =0;
        p->position.y =0;
        p->keys[0] = 0;
        p->keys[1] = 0;
        p->keys[2] = 0;
        p->keys[3] = 0;
        p->brushSize =0;
        p->color = 0;
        if( p->spriteLeft != NULL )
            SDL_DestroyTexture( p->spriteLeft );
        if( p->spriteRight != NULL )
            SDL_DestroyTexture( p->spriteRight );
        free( p );
    }
    if( p==NULL )
        return 0;
    return -1;
}

static player* allocPlayer()
{
    player* temp;
    temp = malloc(sizeof(player));
    if(temp == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Memory error");
    return temp;
}

static int initPlayer(player* p)
{
  int ret = EXIT_SUCCESS;

  if(p == NULL)
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Player isn't allocated");
    ret = EXIT_FAILURE;
  }
  else if( p->isdef == SDL_TRUE )
  {
    SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,
		  "Player %s is almost allocated, will ignore it", p->name );
  }
  else
  {
    p->isdef = SDL_TRUE;
    p->scoreP = 0.0;

    p->Painter = createSkeletonPainter();
    if(p->Painter == NULL)
    {
      SDL_LogError( SDL_LOG_CATEGORY_APPLICATION,
		    "Can't allocate painter for Player %s", p->name );
      deletePlayer(p);
      ret = EXIT_FAILURE;
    }
  }
  return ret;
}

void setDirectionX( player* p, const Direction dx )
{
    if(p != NULL)
    {
        if( p->dir.x == dx )
            p->dir.y = DIR_STOP;
        p->dir.x = dx;
    }
}

void setDirectionY( player* p, const Direction dy )
{
    if(p != NULL)
    {
        if( p->dir.y == dy )
            p->dir.x = DIR_STOP;
        p->dir.y = dy;
    }
}

void setDirection( player* p, const Direction dx, const Direction dy)
{
    if(p != NULL)
    {
        setDirectionX(p, dx);
        setDirectionY(p, dy);
    }
}

int deletePlayer( player* play )
{
    int ret = EXIT_SUCCESS;
    if( play != NULL)
    {
        if( play->isdef == SDL_TRUE )
        {
            if( play->Painter != NULL )
                deletePainter( play->Painter );
            else
            {
                SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                             "Sub Painter of player (%s) isn't allocated, it's not normally.", play->name );
                ret = EXIT_FAILURE;
            }
	    play->scoreP = 0.0;
	    play->isdef = SDL_FALSE;
        }
        else
        {
            SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                         "Player isn't defined, he's probably not still created or some errors happened" );
            ret = EXIT_FAILURE;
        }
	free(play);
    }
    else
    {
        SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                        "Player is not allocated");
        ret = EXIT_FAILURE;
    }
    return ret;
}

void setScore(player* p, double score)
{
    if(p != NULL)
    {
        p->scoreP = score;
    }
}

void setSpeed(player* p, Speed sx, Speed sy){
  if (p != NULL){
    p->speed.x = sx;
    p->speed.y = sy;
  }
}

/** \fn player* createPlayer()
 *  \brief Function that create a player in interaction with user
 *  \return A pointer to the created player if success, NULL otherwise.
 *
 *  \todo Change the way to preconfigured players.
 */
player* createPlayer()
{
    static unsigned char actual_id = 0;
    player* p = NULL;
    SDL_Color* color = NULL;

    if( (p = allocPlayer()) != NULL)
    {
        if (initPlayer(p) != EXIT_FAILURE)
        {
        p->id = actual_id;
        color = &(p->Painter->struct_color);
        printf( "Please enter a name for that young player (31 letters max):" );
        readline( p->name, NAME_STRING_MAX );
        printf( "Now type the three (r,g,b) components of his color :" );
        scanf( "%3u %3u %3u", &color->r,&color->g,&color->b );
        CLEAR_BUFFER;
        if  ( color->r + color->g + color->b <= ( UINT8_MAX*3 ))
        {
            if( data->pixelformat != NULL )
            {
                color->a = SDL_ALPHA_OPAQUE;
                setColor(p->Painter,SDL_MapRGB(data->pixelformat,color->r,color->g,color->b));
                setBrushSize(p->Painter, BRUSH_NORMAL);
                setSpeed(p, SPEED_AVERAGE, SPEED_AVERAGE);
                setDirection(p, DIR_STOP, DIR_STOP);
                setScore(p, 0.0);

                switch(p->id)
                {
                    case 0:
                        setPosition(p->Painter,    (data->window_width/4),
                                                        (data->window_height/4) );
                        setCtrlKeys(p->Painter, SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN);
                        break;
                    case 1:
                        setPosition(p->Painter,    3*(data->window_width/4),
                                                        (data->window_height/4) );
                        setCtrlKeys(p->Painter, SDLK_d, SDLK_q ,SDLK_z ,SDLK_s);
                        break;
                    case 2:
                        setPosition(p->Painter,    (data->window_width/4),
                                                        (data->window_height/4) );
                        setCtrlKeys(p->Painter, SDLK_m, SDLK_k, SDLK_o, SDLK_l);
                        break;
                    case 3:
                        setPosition(p->Painter,    3*(data->window_width/4),
                                                        3*(data->window_height/4) );
                        setCtrlKeys(p->Painter, SDLK_6, SDLK_4, SDLK_8, SDLK_5);
                        break;
                    default:
                        SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                                    "Actual id is invalid : %d", actual_id);
                        setPosition(p->Painter, 42,42);
                        setCtrlKeys(p->Painter, SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN);
                        break;

                }

                p->Painter->spriteLeft = IMG_LoadTexture( *data->renderer,
                                              "pics/paintbrush_toleft.png" );
                p->Painter->spriteRight = IMG_LoadTexture( *data->renderer,
                                               "pics/paintbrush_toright.png" );
                SDL_QueryTexture( p->Painter->spriteLeft, NULL, NULL,
                                  &( p->Painter->position.w ), &( p->Painter->position.h ) );
                p->Painter->activeSprit = &p->Painter->spriteLeft;
            }
        }
    }
    }
    /* Creation Phase end  */
    actual_id = (actual_id != data->numberOfPlayer) ? (actual_id + 1) : (0);
    return p;
}

void movePlayer( player* p )
{
    if( p==NULL );
    else
    {
        /* Update player position*/
        p->Painter->position.y += ( p->speed.y )*( p->dir.y );
        p->Painter->position.x += ( p->speed.x )*( p->dir.x );
        /* RIGHT */
        if( p->Painter->position.x >= ( signed )( data->window_width - p->Painter->position.w ) )
        {
            setPosition( p->Painter, data->window_width- p->Painter->position.w, -1 );
        }
        /* LEFT */
        else if( p->Painter->position.x < ( signed )0 )
        {
            setPosition( p->Painter, 0, -1 );
        }
        /* DOWN */
        if( p->Painter->position.y >= ( signed )( data->window_height - p->Painter->position.h ) )
        {
            setPosition(p->Painter, -1, data->window_height - p->Painter->position.h);
        }
        /* HIGH */
        else if( p->Painter->position.y < 0 )
            setPosition(p->Painter, -1, 0);
    }
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
