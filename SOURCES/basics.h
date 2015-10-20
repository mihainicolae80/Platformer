#ifndef BASICS_H_INCLUDED
#define BASICS_H_INCLUDED

#include <iostream>
#include <sstream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "base.h"

#define DEFAULT_SCREEN_WIDTH  1920
#define DEFAULT_SCREEN_HEIGHT 1080


/**
//Debug
extern ofstream DEBUG_outf;
extern ofstream DEBUG_FileLoadFails;
extern SDL_Surface *DEBUG_ExcMarkSurf;
extern SDL_Texture *DEBUG_ExcMarkTex;
**/

using namespace std;


extern double SCALE;


//Basic value and string
void ctos( char carray[], string &strnew );
double module( double x );
void itos(int nr,string &newstr );
void GAME_strcpy( char *dest,const char *sourc );
void GAME_strcat( char *dest,const char *sourc );

//Graphics
SDL_Surface *LoadSurf(string file);
SDL_Texture *LoadTex(string file);
SDL_Texture* ENGINE_RenderText_Texture( TTF_Font *font,const char *text,SDL_Color color );
void ENGINE_DestroyTexture( SDL_Texture **tex );
void ApplyTex(int x,int y,SDL_Texture *tex,SDL_Rect *clip = NULL);
void ApplyTex_straight(int x,int y,SDL_Texture *tex,SDL_Rect *clip = NULL);
void LoadingTitle( int percent );

#endif // BASICS_H_INCLUDED
