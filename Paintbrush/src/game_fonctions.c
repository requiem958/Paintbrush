/** \file game_fonctions.c
 *  \brief Implement static and public core parts
 *  \author Marius Monnier
 *  \version 0.1
 */

#include "game_fonctions.h"


static void displaySprites(void);
static void drawPaintersRect(void);
static void game( void );
static int set_scores(void);
static GameState gestionClavier( SDL_Event event,
                          int numberOfPainters );

extern GameData* data;
extern player* players[];

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
        if( ( players[index] = createPlayer() ) != (player*)NULL )
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
                    movePlayer( players[index] );
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
                    setDirectionY( players[i], DIR_REVERSE );
                }
                else if( key == players[i]->Painter->keys[CTRL_KEY_DOWN] )
                {
                    setDirectionY( players[i], DIR_ACTIVE );
                }
                else if( key == players[i]->Painter->keys[CTRL_KEY_RIGHT] )
                {
                    setDirectionX( players[i], DIR_ACTIVE );
                    players[i]->Painter->activeSprit = &( players[i]->Painter->spriteRight );
                }
                else if( key == players[i]->Painter->keys[CTRL_KEY_LEFT] )
                {
                    setDirectionX( players[i], DIR_REVERSE );
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

GameData* createGameData(SDL_Window** window, SDL_Renderer** renderer, char *appName)
{
    GameData* data = NULL;
    data = malloc(sizeof(GameData));
    if(data != NULL)
    {
        data->window = window;
        SDL_GetWindowSize(*window, &data->window_width, &data->window_height);
        data->renderer = renderer;

        data->appName = appName;
        data->pixelformat = SDL_AllocFormat(SDL_GetWindowPixelFormat(*window));
        if(data->pixelformat == NULL)
        {
            free(data);
            data = NULL;
        }
        else
        {
            data->display.background = IMG_LoadTexture(*renderer, "pics/background.jpg");
            /*  Create transparent foreground texture */
            SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);
            data->display.foreground = SDL_CreateTexture(*renderer, SDL_GetWindowPixelFormat(*window),
                                        SDL_TEXTUREACCESS_TARGET, data->window_width, data->window_height);
            if(data->display.foreground != NULL)
                clear_texture(data->display.foreground, *renderer);
            /*  Surface Creation */
            data->display.readable_foreground = SDL_CreateRGBSurface(0,
                    data->window_width, data->window_height,
                    data->pixelformat->BitsPerPixel, 0,0,0,0);
            SDL_ConvertSurface(data->display.readable_foreground, data->pixelformat, 0);
            if(data->display.readable_foreground == NULL)
            {
                fprintf(stderr, "Error during surface creation SDL : %s\n", SDL_GetError());
                SDL_DestroyTexture(data->display.background);
                SDL_DestroyTexture(data->display.foreground);
                free(data);
                data = NULL;
            }
            else
                SDL_FillRect(data->display.readable_foreground, NULL, 0);

        }
    }
    return data;
}

int initSDLSystems( FPSmanager* manager )
{
    int ret = EXIT_SUCCESS;
    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS )  == -1 || !IMG_Init( IMG_INIT_PNG ) )
    {
        fprintf( stderr, "Initialisation erreur -> %s\n", SDL_GetError() );
        ret = EXIT_FAILURE;
    }
    else
    {
        SDL_LogSetAllPriority( SDL_LOG_PRIORITY_DEBUG );
        SDL_initFramerate( (FPSmanager*) &manager );
        if( manager == NULL )
        {
            fprintf( stderr, "Can't init FPSManager : %s\n", SDL_GetError() );
            ret = EXIT_FAILURE;
        }
        else
        {
            if( SDL_setFramerate( (FPSmanager*) &manager, NB_IMG_PER_SECOND ) == -1 )
            {
                fprintf( stderr, "Can't set framerate to %d : %s\n", NB_IMG_PER_SECOND, SDL_GetError() );
                ret = EXIT_FAILURE;
            }
        }
    }
    return ret;
}

int initWindowAndRenderer( SDL_Window** window, SDL_Renderer** renderer,
                           const unsigned int width, const unsigned int height,
                           const char* title )
{
    int ret = EXIT_SUCCESS;
    *window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE );
    if( *window == NULL )
    {
        ret = EXIT_FAILURE;
        fprintf( stderr, "Can't create window : %s", SDL_GetError() );
    }
    else
    {
        *renderer = SDL_CreateRenderer( *window, -1,
                                        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED |SDL_RENDERER_TARGETTEXTURE );
        if( *renderer == NULL )
        {
            ret = EXIT_FAILURE;
            fprintf( stderr, "Can't create renderer : %s\nWe destroy Window.", SDL_GetError() );
            SDL_DestroyWindow( *window );
        }
        else
        {
            SDL_SetRenderDrawColor( *renderer, 0,0,0,SDL_ALPHA_OPAQUE );
            SDL_RenderClear( *renderer );
            SDL_RenderPresent( *renderer );
        }
    }
    return ret;
}


