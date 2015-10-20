#include "basics.h"
#include "cmath"

double SCALE;


void ctos( char carray[], string &strnew ){
int i;
strnew.erase();

while( carray[0] == ' ' )
{
    for( i = 1; (unsigned)i < SDL_strlen( carray ); i++ )
    carray[i-1] = carray[i];
    carray[i-1] = '\0';
}

for( int i = 0; carray[i] != '\0'; i++ )
strnew += carray[i];
}
double module( double x ){
if( x < 0 )
return x * -1;
return x;
}
void itos(int nr,string &newstr ){
std::stringstream ssaux;
newstr.erase();
ssaux<<nr;
ssaux>>newstr;
}
void GAME_strcpy( char *dest,const char *sourc ){
int len_sourc,i;
len_sourc = SDL_strlen( sourc );

for( i = 0; i < len_sourc; i++ )
dest[i] = sourc[i];
dest[len_sourc] = '\0';
}
void GAME_strcat( char *dest,const char *sourc ){
int len_dest,len_sourc,i;
len_dest  = SDL_strlen( dest );
len_sourc = SDL_strlen( sourc );

for( i = 0; i < len_sourc; i++ )
dest[i + len_dest ] = sourc[i];
dest[len_sourc + len_dest ] = '\0';
}

SDL_Surface *LoadSurf(string file){
SDL_Surface *loadedimg = NULL;

loadedimg = IMG_Load( file.c_str() );

if( loadedimg == NULL )
{
    //DEBUG.fout( FILE_FLF, (string)"load fail: " + file );
    //DEBUG.fout( FILE_FLF, (string)"reason: "    + SDL_GetError() + (string)"\n" );
}

return loadedimg;
}
SDL_Texture *LoadTex(string file){
SDL_Texture *loadedtex = NULL;

loadedtex = IMG_LoadTexture(RENDERER_MAIN,file.c_str() );

if( loadedtex == NULL )
{
    //DEBUG.fout( FILE_FLF, (string)"load fail: " + file );
    //DEBUG.fout( FILE_FLF, (string)"reason: "    + SDL_GetError() + (string)"\n" );
}

return loadedtex;
}
void ApplyTex(int x,int y,SDL_Texture *tex,SDL_Rect *clip){
SDL_Rect pos;

SCALE = (double)SCREEN_WIDTH/DEFAULT_SCREEN_WIDTH;

pos.x = x * SCALE   +   VIEWPORT_x;
pos.y = y * SCALE   +   VIEWPORT_y    //Properly place ---- add viewport changes
        + ( SCREEN_HEIGHT - (double)SCREEN_WIDTH/16*9 )/2 ;    //CENTER


    if( clip != NULL )
    {
        pos.w = clip->w;
        pos.h = clip->h;
    }
    else
    SDL_QueryTexture( tex,NULL,NULL,&pos.w,&pos.h );

    pos.w    = ceil( pos.w * SCALE );
    pos.h    = ceil( pos.h * SCALE );


SDL_RenderCopy( RENDERER_MAIN,tex,clip,&pos );
}
void ApplyTex_straight(int x,int y,SDL_Texture *tex,SDL_Rect *clip){
SDL_Rect pos;

SCALE = (double)SCREEN_WIDTH/DEFAULT_SCREEN_WIDTH;

pos.x = x ; // Straigth display
pos.y = y ;


    if( clip != NULL )
    {
        pos.w = clip->w;
        pos.h = clip->h;
    }
    else
    SDL_QueryTexture( tex,NULL,NULL,&pos.w,&pos.h );

    pos.w   *=   SCALE;
    pos.h   *=   SCALE;


SDL_RenderCopy( RENDERER_MAIN,tex,clip,&pos );
}

SDL_Texture* ENGINE_RenderText_Texture( TTF_Font *font,const char *text,SDL_Color color ){

SDL_Surface *aux_surf = NULL;
SDL_Texture *dest = NULL;

aux_surf = TTF_RenderText_Blended( font,text,color );
dest = SDL_CreateTextureFromSurface( RENDERER_MAIN, aux_surf );
return dest;
}
void         ENGINE_DestroyTexture( SDL_Texture **tex ){

if( &tex != NULL )
{
    SDL_DestroyTexture( *tex );
    *tex = NULL;
}
}
