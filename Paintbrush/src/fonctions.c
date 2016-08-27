/** \file fonctions.c
 *  \brief Implementation of some functions that can be used anywhere
 *  \author Marius Monnier
 *  \version 0.1
 */

#include "defines.h"
#include "fonctions.h"
/** \fn void str_replace( char** s, int token, int replacement )
 *  \brief Function that replace one token by another in a given string
 *  \param  s pointer to the string that will be modified
 *  \param  token Character to search in string
 *  \param  replacement Character that will replace token
 *
 * That function did not return something because the original string is
 * modified. We use strchr() to find the token.
 *
 *  \todo Some validity tests for token and replacement.
 */
void str_replace( char** s, int token, int replacement )
{
    int* pointer = NULL;
    pointer = ( int* )strchr( *s, token );
    if( pointer != NULL )
    {
        *pointer = replacement;
    }
}

void dummy()
{
    ;
}

/** \fn int readline( char* s, int n )
 *  \brief Function that read a line securely and make it a valid string
 *  \param  s pointer that will store the string
 *  \param  n number of character that will be read
 *  \return EXIT_SUCCESS if success, EXIT_FAILURE otherwise.
 *
 *  That function use fgets to create the string, and replace the final '\n'
 *  with a '\0' to make the string valid.
 *  \todo A way to describe the error ?
 */
int readline( char* s, int n )
{
    int ret = EXIT_SUCCESS;
    char *error = NULL;
    error = fgets( s, n, stdin );
    if (error != NULL)
    {
        str_replace( &s, '\n', '\0' );
    }
    else
    {
        ret = EXIT_FAILURE;
    }
    return ret;
}

/** \fn Uint32 obtenirPixel( SDL_Surface* surface, int x, int y )
 *  \brief Function to extract the value of a pixel at given coordinates
 *  \param  surface pointer to the surface with the pixels.
 *  \param  x coordinate in x of the pixel
 *  \param  y coordinate in y of the pixel
 *  \return the coded value of the pixel, or zero if error.
 *
 *
 */
Uint32 getPixel( SDL_Surface* surface, int x, int y )
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;

    Uint8* p = ( Uint8* )surface->pixels + y * surface->pitch + x *
               nbOctetsParPixel;

    switch( nbOctetsParPixel )
    {
    case 1:
        return *p;

    case 2:
        return *( Uint16* )p;

    case 3:

        if( SDL_BYTEORDER == SDL_BIG_ENDIAN )
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *( Uint32* )p;

    default:
        return 0;
    }
}

/** \fn void clear_texture(SDL_Texture *texture, SDL_Renderer *renderer)
 *  \brief Function that set a texture to black transparent texture (clear everything)
 *  \param  texture pointer to the texture
 *  \param  renderer pointer to the renderer that is used
 */
void clear_texture(SDL_Texture *texture, SDL_Renderer *renderer)
{
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0,0,0,SDL_ALPHA_TRANSPARENT);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderPresent(renderer);
}

/** \fn int setRenderDrawColor(SDL_Renderer* renderer, SDL_Color *color)
 *  \brief Convenience function to set the color from a struct
 *  \param  renderer pointer to the renderer that will be modified
 *  \param  color   Structure that store the color components
 */
int setRenderDrawColor(SDL_Renderer* renderer, SDL_Color *color)
{
    int ret = EXIT_SUCCESS;
    if(renderer != NULL && color != NULL)
    {
        ret = SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    }
    else
        ret = EXIT_FAILURE;
    return ret;
}
