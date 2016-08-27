/** \file painters.c
 *  \brief Implement static and public painters related functions
 *  \author Marius Monnier
 *  \version 0.1
 */

#include "global_types.h"
#include "painters.h"

extern GameData* data;


static painter_ptr allocPainter( void )
{
    painter_ptr testing = NULL;
    testing = malloc( sizeof( painter ) );
    return testing;
}

static void initPainter(painter_ptr paint)
{
    if(paint != NULL)
    {
        paint->activeSprit = NULL;
        paint->brushSize = BRUSH_NORMAL;
        paint->dir.x = DIR_STOP;
        paint->dir.y = DIR_STOP;
        paint->position.h =0;
        paint->position.w =0;
        paint->position.x =0;
        paint->position.y =0;

        paint->speed.x = SPEED_AVERAGE;
        paint->speed.y = SPEED_AVERAGE;
    }
}

painter_ptr createSkeletonPainter()
{
    painter_ptr paint = NULL;

    paint = allocPainter();
    if(paint != NULL)
        initPainter(paint);
    else
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Memory error (painter alloc)");
    return paint;
}

int deletePainter( painter_ptr p )
{
    if( p != ( painter_ptr )NULL )
    {
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
        p->speed.x = SPEED_NULL;
        p->speed.y = SPEED_NULL;
        p->dir.x = DIR_STOP;
        p->dir.y = DIR_STOP;
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

void movePainter( painter_ptr p )
{
    if( p==NULL );
    else
    {
        /* Update player position*/
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

void setDirectionX( painter_ptr p, const Direction dx )
{
    if(p != NULL)
    {
        if( p->dir.x == dx )
            p->dir.y = DIR_STOP;
        p->dir.x = dx;
    }
}

void setDirectionY( painter_ptr p, const Direction dy )
{
    if(p != NULL)
    {
        if( p->dir.y == dy )
            p->dir.x = DIR_STOP;
        p->dir.y = dy;
    }
}

void setDirection( painter_ptr p, const Direction dx, const Direction dy)
{
    if(p != NULL)
    {
        setDirectionX(p, dx);
        setDirectionY(p, dy);
    }
}

void setColor( painter_ptr p, const Uint32 c )
{
    if(p != NULL)
    {
        p->color = c;
    }
}

void setBrushSize(painter_ptr p, const BrushSize size)
{
    if(p != NULL)
    {
        p->brushSize = size;
    }
}

void setPosition( painter_ptr p, const int x, const int y )
{
    if( p != NULL )
    {
        if(x != -1)
            p->position.x = x;
        if(y != -1)
            p->position.y = y;
    }
}

void setSpeed( painter_ptr p, const Speed speedx, const Speed speedy)
{
    if(p != NULL)
    {
        p->speed.x = speedx;
        p->speed.y = speedy;
    }
}

void setScore(Player_ptr p, double score)
{
    if(p != NULL)
    {
        p->scoreP = score;
    }
}

void setCtrlKeys(painter_ptr p,
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
