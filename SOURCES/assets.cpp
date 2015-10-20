#include "assets.h"

void CLS_ASSETS::init(){
int i;

for( i = 0; i < MAXIMUM_NORMAL_TEX; i++ )
    NORMAL_TEX[ i ] = NULL;

for( i = 0; i < MAXIMUM_BG_TEX; i++ )
    BG_TEX[ i ] = NULL;

_NULL_TEX = LoadTex( "Data//Sprites//NORMAL//-1.png" );
}
SDL_Texture* CLS_ASSETS::getTex_NORMAL(int x){
stringstream ssaux;

if( x == -1 ) return _NULL_TEX;//work work
else
if( NORMAL_TEX[x] == NULL )
{
    ssaux << "Data//Sprites//NORMAL//";
    ssaux << x <<".png";
    NORMAL_TEX[x] = LoadTex( ssaux.str() );
}

return NORMAL_TEX[x];
}
SDL_Texture* CLS_ASSETS::getTex_BG(int x){
stringstream ssaux;

if( x == -1 ) return _NULL_TEX;//work work
else
if( BG_TEX[x] == NULL )
{
    ssaux << "Data//Sprites//BG//";
    ssaux << x <<".png";
    BG_TEX[x] = LoadTex( ssaux.str() );
}

return BG_TEX[x];
}
