/** \file main.c
 *  \brief Entry point of program
 *  \author Marius Monnier
 *  \version 0.1
 */

#include <stdlib.h>
#include <stdio.h>
#include "global_inc.h"

/**< Global parameters var*/
GameData* data = NULL;
/**< Global player tab*/
player* players[MAX_PLAYERS];

int main( void )
{
  int ret = EXIT_SUCCESS;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  FPSmanager* manager = NULL;

  if( initSDLSystems( manager ) == EXIT_FAILURE )
    {
      SDL_LogError( SDL_LOG_CATEGORY_ERROR,
		    "Can't correctly init sdl systems ! (see above messages)\n\
                        SDL says : %s\n", SDL_GetError() );
      ret = EXIT_FAILURE;
    }
  else
    {
      if( initWindowAndRenderer( &window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT,
				 "Paintbrush" ) == EXIT_FAILURE )
        {
	  SDL_LogError( SDL_LOG_CATEGORY_ERROR,
			"Problem during window and renderer initialisation \
                            (see above messages) \n \
                            SDL Message : %s\n", SDL_GetError() );
	  ret = EXIT_FAILURE;
        }
      else
        {
	  data = createGameData( &window, &renderer, "Paintbrush" );
	  if( data == NULL )
            {
	      SDL_LogError( SDL_LOG_CATEGORY_ERROR,
			    "Problem during data initialisation \n \
                              SDL Message : %s", SDL_GetError() );
	      ret = EXIT_FAILURE;
            }
	  else
            {
	      data->current_state = STATE_CONFIGURATION;
	      data->manager = &manager;

	      //Error Management
	      if( data->display.foreground == NULL )
                {
		  SDL_LogError( SDL_LOG_CATEGORY_ERROR,
				"Can't create texture Foreground. %s",
				SDL_GetError() );
		  ret = EXIT_FAILURE;
                }
	      if( data->pixelformat->format == 0 )
                {
		  SDL_LogError( SDL_LOG_CATEGORY_ERROR,
				"Can't create pixel format of that window : %s",
				SDL_GetError() );
		  ret = EXIT_FAILURE;
                }

	      //Main Loop
	      if( ret != EXIT_FAILURE )
                {
		  do
                    {
		      launch_menu();

		      launch_game();

		      if (data->current_state == STATE_QUIT)
			launch_replay();

		      deleteAllPlayers();

		      clear_texture(data->display.foreground, *data->renderer);
		      SDL_FillRect(data->display.readable_foreground, NULL, 0);
                    }
		  while( ret == EXIT_SUCCESS && data->current_state == STATE_PLAYING );
                }
	      SDL_FreeFormat( data->pixelformat );
	      SDL_FreeSurface( data->display.readable_foreground);
	      SDL_DestroyTexture( data->display.background );
	      SDL_DestroyTexture( data->display.foreground );
	      SDL_DestroyRenderer( *data->renderer );
	      SDL_DestroyWindow( *data->window );
	      free( data );
            }
        }
      quit_lib_systems();
    }
  return ret;
}
