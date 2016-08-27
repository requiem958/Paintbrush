/** \file quit.c
 *  \brief Define functions used at exit
 *  \author Marius Monnier
 *  \version 0.1
 */

#include "defines.h"
#include "quit.h"


void quit_lib_systems()
{
    SDL_Quit();
    IMG_Quit();
}
