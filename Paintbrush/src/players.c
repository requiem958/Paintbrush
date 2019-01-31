/** \file Players.c
*  \brief Implement public Players related functions and static painters related functions
*  \author Marius Monnier
*  \version 0.1
*/

#include "types.h"
#include "players.h"

extern GameData* data;
extern Player* Players[];

/* Allocator */

static Player* allocPlayer()
{
  Player* temp;
  temp = malloc(sizeof(Player));
  if(temp == NULL)
  SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Memory error");
  return temp;
}

/* Setters */

void setSpriteRight(Player* p, SDL_Texture* t)
{
  if (p != NULL)
  {
    p->spriteRight = t;
  }
}

void setSpriteLeft(Player* p, SDL_Texture* t)
{
  if (p != NULL)
  {
    p->spriteLeft = t;
  }
}

void setActiveSprite(Player* p, SDL_Texture** t)
{
  if (p != NULL)
  {
    if (p->activeSprite == t)
    ;
    else if (*t == p->spriteRight || *t == p->spriteLeft)
    p->activeSprite = t;
    else
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Attempt to defigurate Player (%s)", p->name);
  }
}

void setPosition( Player* p, const int x, const int y )
{
  if( p != NULL )
  {
    if(x != -1)
    p->position.x = x;
    if(y != -1)
    p->position.y = y;
  }
}

void setBrushSize(Player* p, const BrushSize size)
{
  if(p != NULL)
  {
    p->size = size;
    p->position.h = p->position.w = size;
  }
}

void setCtrl(Player *p, const int index, const SDL_Keycode key)
{
  if(p != NULL)
  {
    if (index >= 0 && index < 4)
    p->keys[index] = key;
    else
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Forbidden key index: %d", index);
  }
}

void setCodedColor( Player* p, const Uint32 c )
{
  if(p != NULL)
  {
    p->color = c;
  }
}

void setStructColor( Player* p, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a )
{
  if(p != NULL)
  {
    p->struct_color.r = r;
    p->struct_color.g = g;
    p->struct_color.b = b;
    p->struct_color.a = a;
  }
}

void setDef(Player* p, const SDL_bool b)
{
  if (p != NULL)
  p->isdef = b;
}

void setName(Player* p, const char* name, const unsigned int size)
{
  if (p != NULL)
  {
    if (size > 0 && size < NAME_STRING_MAX)
    strcpy(p->name,name);
    else
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Name out of range (length) : %s", name);
  }
}

void setId(Player* p, const char id)
{
  if (p != NULL)
  {
    if (id >= 0 && id < MAX_PLAYERS)
    p->id = id;
    else
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Forbidden id index: %d ; %s", id, p->name);
  }
}

void setScore(Player* p, double score)
{
  if(p != NULL)
  {
    p->scoreP = score;
  }
}

void setSpeed(Player* p, Speed sx, Speed sy)
{
  if (p != NULL)
  {
    p->speed.x = sx;
    p->speed.y = sy;
  }
}

void setDirectionX( Player* p, const Direction dx )
{
  if(p != NULL)
  {
    if( p->dir.x == dx )
    p->dir.y = DIR_STOP;
    p->dir.x = dx;
  }
}

void setDirectionY( Player* p, const Direction dy )
{
  if(p != NULL)
  {
    if( p->dir.y == dy )
    p->dir.x = DIR_STOP;
    p->dir.y = dy;
  }
}

void setDirection( Player* p, const Direction dx, const Direction dy)
{
  if(p != NULL)
  {
    setDirectionX(p, dx);
    setDirectionY(p, dy);
  }
}

/*Initialisation*/

static int initPlayer(Player* p)
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
      setDef(p,SDL_TRUE);
      setScore(p,0.0);
      setSpriteRight(p,NULL);
      setSpriteLeft(p,NULL);
      setActiveSprite(p,&p->spriteRight);
      setPosition(p,0,0);
      setBrushSize(p,BRUSH_NORMAL);
    }
    return ret;
  }

  /*Destructor */

  int deletePlayer( Player* play )
  {
    int ret = EXIT_SUCCESS;
    if( play != NULL)
    {
      if( play->isdef == SDL_TRUE )
      {
        if (play->spriteLeft != NULL)
        SDL_DestroyTexture(play->spriteLeft);
        if (play->spriteRight != NULL)
        SDL_DestroyTexture(play->spriteRight);
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

      /*High level Functions */



      /** \fn Player* createPlayer()
      *  \brief Function that create a Player in interaction with user
      *  \return A pointer to the created Player if success, NULL otherwise.
      *
      *  \todo Change the way to preconfigured Players.
      */
      Player* createPlayer()
      {
        static unsigned char actual_id = 0;
        Player* p = NULL;
        SDL_Color* color = NULL;

        if( (p = allocPlayer()) != NULL)
        {
          if (initPlayer(p) != EXIT_FAILURE)
          {
            p->id = actual_id;
            color = &(p->struct_color);
            printf( "Please enter a name for that young Player (31 letters max):" );
            readline( p->name, NAME_STRING_MAX );
            printf( "Now type the three (r,g,b) components of his color :" );
            scanf( "%3u %3u %3u", &color->r,&color->g,&color->b );
            CLEAR_BUFFER;
            if  ( color->r + color->g + color->b <= ( UINT8_MAX*3 ))
            {
              if( data->pixelformat != NULL )
              {
                color->a = SDL_ALPHA_OPAQUE;
                setCodedColor(p,SDL_MapRGB(data->pixelformat,color->r,color->g,color->b));
                setBrushSize(p, BRUSH_NORMAL);
                setSpeed(p, SPEED_AVERAGE, SPEED_AVERAGE);
                setDirection(p, DIR_STOP, DIR_STOP);
                setScore(p, 0.0);

                switch(p->id)
                {
                  case 0:
                  setPosition(p,    (data->window_width/4),
                  (data->window_height/4) );
                  setCtrl(p,0, SDLK_RIGHT);
                  setCtrl(p,1, SDLK_LEFT);
                  setCtrl(p,2, SDLK_UP);
                  setCtrl(p,3, SDLK_DOWN);
                  break;
                  case 1:
                  setPosition(p,    3*(data->window_width/4),
                  (data->window_height/4) );
                  setCtrl(p,0, SDLK_d);
                  setCtrl(p,1, SDLK_q);
                  setCtrl(p,2, SDLK_z);
                  setCtrl(p,3, SDLK_s);
                  break;
                  case 2:
                  setPosition(p,    (data->window_width/4),
                  (data->window_height/4) );
                  setCtrl(p,0, SDLK_m);
                  setCtrl(p,1, SDLK_k);
                  setCtrl(p,2, SDLK_o);
                  setCtrl(p,3, SDLK_l);
                  break;
                  case 3:
                  setPosition(p,    3*(data->window_width/4),
                  3*(data->window_height/4) );
                  setCtrl(p,0, SDLK_6);
                  setCtrl(p,1, SDLK_4);
                  setCtrl(p,2, SDLK_8);
                  setCtrl(p,3, SDLK_5);
                  break;
                  default:
                  SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                    "Actual id is invalid : %d", actual_id);
                    setPosition(p, 42,42);
                    setCtrl(p,0, SDLK_RIGHT);
                    setCtrl(p,1, SDLK_LEFT);
                    setCtrl(p,2, SDLK_UP);
                    setCtrl(p,3, SDLK_DOWN);
                    break;

                  }

                  p->spriteLeft = IMG_LoadTexture( *data->renderer,
                    "pics/paintbrush_toleft.png" );
                  p->spriteRight = IMG_LoadTexture( *data->renderer,
                      "pics/paintbrush_toright.png" );
                  SDL_QueryTexture( p->spriteLeft, NULL, NULL,
                                    &( p->position.w ),
                                    &( p->position.h ));
                  p->activeSprite = &p->spriteLeft;
                      }
                    }
                  }
                }
                /* Creation Phase end  */
                actual_id = (actual_id != data->numberOfPlayer) ? (actual_id + 1) : (0);
                return p;
              }

              void movePlayer( Player* p )
              {
                if( p==NULL );
                else
                {
                  /* Update Player position*/
                  p->position.y += ( p->speed.y )*( p->dir.y );
                  p->position.x += ( p->speed.x )*( p->dir.x );
                  /* RIGHT */
                  if( p->position.x >= ( signed )( data->window_width - p->position.w ) )
                  {
                    setPosition( p, data->window_width- p->position.w, -1 );
                  }
                  /* LEFT */
                  else if( p->position.x < ( signed )0 )
                  {
                    setPosition( p, 0, -1 );
                  }
                  /* DOWN */
                  if( p->position.y >= ( signed )( data->window_height - p->position.h ) )
                  {
                    setPosition(p, -1, data->window_height - p->position.h);
                  }
                  /* HIGH */
                  else if( p->position.y < 0 )
                  setPosition(p, -1, 0);
                }
              }

              int deleteAllPlayers()
              {
                int ret = EXIT_SUCCESS;
                while( data->numberOfPlayer-- >0 )
                {
                  if( Players[data->numberOfPlayer]->isdef
                    && Players[data->numberOfPlayer] != NULL )
                    {
                      if( deletePlayer( Players[data->numberOfPlayer] ) != EXIT_SUCCESS )
                      {
                        SDL_LogError( SDL_LOG_CATEGORY_ERROR,
                          "During Player deleting (see above)" );
                          ret = EXIT_FAILURE;
                        }
                      }
                    }

                    return ret;
                  }
