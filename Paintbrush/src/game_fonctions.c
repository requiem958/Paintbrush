/** \file game_fonctions.c
 *  \brief Implement static and public core parts
 *  \author Marius Monnier
 *  \version 0.1
 */

#include "defines.h"
#include "fonctions.h"
#include "game_fonctions.h"
#include "painters.h"
#include "players.h"

static void displaySprites(void);
static void drawPaintersRect(void);
static void game( void );
static int set_scores(void);
static GameState gestionClavier( SDL_Event event,
                          int numberOfPainters );

extern GameData* data;
extern Player* players[];

void launch_menu(void)
{
    unsigned int index;

    do
    {
        printf( "How many players ? [1 à 4] : " );
        scanf( "%1ud", &data->numberOfPlayer );
        CLEAR_BUFFER;
    }
    while( data->numberOfPlayer < 1 || data->numberOfPlayer > MAX_PLAYERS );
    for( index = 0; index < data->numberOfPlayer; index++ )
    {
        if( ( players[index] = createPlayer() ) != (Player*)NULL )
        {
            SDL_LogMessage( SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
            "Player (%d) created with success", index );
        }
        else
        {
            SDL_LogError( SDL_LOG_CATEGORY_ERROR,
                          "During player creation (see above message)" );
            deletePlayer( players[index] );
            break;
        }
    }
}

void launch_game(void)
{
    char response;

    printf( "Game [Y/N] :" );
    scanf( "%c", &response );
    CLEAR_BUFFER;
    if (response == 'Y' || response == 'y')
        game();
}

void launch_replay(void)
{
    char response;

    printf( "Another game ? [Y/N]" );
    scanf( "%1c", &response );
    CLEAR_BUFFER;
    data->current_state = (response == 'Y' || response == 'y' ) ? ( STATE_PLAYING ) : ( STATE_QUIT );
}

static void game( void )
{
    unsigned int t_actu = 0, t_preced = 0;
    long  int delay = 100 K;
    unsigned char index = 0;
    SDL_Event event;

    data->current_state = STATE_PLAYING;
    while( SDL_PollEvent( &event ) || data->current_state != STATE_QUIT )
        {
            if( event.type == SDL_KEYDOWN )
                data->current_state = gestionClavier( event, data->numberOfPlayer );
            if( data->current_state == STATE_PLAYING )
            {
                /* Display functions*/
                displaySprites();
                /* Move player functions */
                for( index = 0; index < data->numberOfPlayer; index++ )
                {
                    movePainter( players[index]->Painter );
                }
                /* Time loop */
                t_actu = SDL_GetTicks();
                if (t_actu - t_preced > 1000)
                {
                    printf( "Encore %ld secondes !\n", delay/1000);
                    delay -= 1000;
                    t_preced = t_actu;
                }
                SDL_framerateDelay( *data->manager );
            }
            if ( event.type == SDL_QUIT || delay < 0)
                data->current_state = STATE_QUIT;
        }

        set_scores();
}

static GameState gestionClavier( SDL_Event event,
                          int numberOfPainters )
{
    int quit = STATE_PLAYING;
    static char isAlreadyPaused = 0;
    unsigned char i = 0;
    SDL_Keycode key = event.key.keysym.sym;
    switch( key )
    {
        case SDLK_ESCAPE:
            quit = STATE_QUIT;
            break;
        case SDLK_DELETE:
            SDL_RenderClear( *data->renderer );
            quit = STATE_PLAYING;
            break;
        case SDLK_p:
            if( !isAlreadyPaused )
            {
                quit = STATE_PAUSED;
                puts( "Pause." );
                isAlreadyPaused = 1;
            }
            else
                quit = STATE_PAUSED;
            break;
        default:
            for( i = 0; i < numberOfPainters; i++ )
            {
                if( key == players[i]->Painter->keys[CTRL_KEY_UP] )
                {
                    setDirectionY( players[i]->Painter, DIR_REVERSE );
                }
                else if( key == players[i]->Painter->keys[CTRL_KEY_DOWN] )
                {
                    setDirectionY( players[i]->Painter, DIR_ACTIVE );
                }
                else if( key == players[i]->Painter->keys[CTRL_KEY_RIGHT] )
                {
                    setDirectionX( players[i]->Painter, DIR_ACTIVE );
                    players[i]->Painter->activeSprit = &( players[i]->Painter->spriteRight );
                }
                else if( key == players[i]->Painter->keys[CTRL_KEY_LEFT] )
                {
                    setDirectionX( players[i]->Painter, DIR_REVERSE );
                    players[i]->Painter->activeSprit = &( players[i]->Painter->spriteLeft );
                }
            }
            quit = STATE_PLAYING;
            break;
    }
    return quit;
}

static int set_scores(void)
{
    SDL_Surface *surface = data->display.readable_foreground;
    SDL_Point pixel;
    unsigned char index = 0;

    for( pixel.x = 0; (unsigned)pixel.x < (unsigned)surface->h; pixel.x++ )
    {
        for( pixel.y = 0; (unsigned)pixel.y < (unsigned)surface->w; pixel.y++ )
        {
            for( index = 0; index < data->numberOfPlayer; index++ )
            {
                if( players[index]->Painter->color == getPixel(surface, pixel.x, pixel.y))
                {

                    players[index]->scoreP++;
                }
            }
        }
    }
    for( index = 0; index < ( unsigned )data->numberOfPlayer; index++ )
    {
        printf("Player %s has %0.2f%% of screen\n", players[index]->name, (players[index]->scoreP*100)/(surface->h*surface->w));
    }
    return 0;
}

static void displaySprites(void)
{
    unsigned char index;
        /* Certitude de dessiner sur la fenêtre VIDE*/
    SDL_SetRenderTarget( *data->renderer, NULL );
    SDL_RenderClear( *data->renderer );
    /* Background -> Foreground -> Each player */
    SDL_RenderCopy( *data->renderer, data->display.background, NULL, NULL );

    drawPaintersRect();

    SDL_SetRenderTarget( *data->renderer, NULL );
    SDL_RenderCopy( *data->renderer, data->display.foreground, NULL, NULL );
    for( index = 0; index < data->numberOfPlayer; index++ )
    {
        SDL_RenderCopy( *data->renderer, *players[index]->Painter->activeSprit,
                        NULL, &players[index]->Painter->position );
    }
    SDL_RenderPresent( *data->renderer );
}
static void drawPaintersRect(void)
{
    unsigned char index;
    SDL_Rect paint;
    SDL_SetRenderTarget( *data->renderer, data->display.foreground );
    for( index = 0; index < data->numberOfPlayer; index++ )
    {
        setRenderDrawColor(*data->renderer, &players[index]->Painter->struct_color);
        paint = players[index]->Painter->position;

        paint.y += paint.h/2;
        paint.h = paint.w = players[index]->Painter->brushSize;
        SDL_RenderFillRect( *data->renderer, &paint );
        SDL_FillRect(data->display.readable_foreground, &paint, players[index]->Painter->color);
    }
}
