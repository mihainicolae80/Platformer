#include "map.h"
#include "assets.h"

void CLS_MAP::init(){
int i,j;
for( i = 0; i < 14;i ++ )
    for( j = 0; j < 24; j++ )
    {
        MAP_NORMAL_SKELETON[i][j] = -1;
        MAP_BG_SKELETON[i][j]     = -1;

        MAP_NORMAL_TEX[i][j]      = NULL;
        MAP_BG_TEX[i][j]          = NULL;
    }
}
void CLS_MAP::load( int cmap ){
std::stringstream ssaux;
std::ifstream FILE;

ssaux <<"Data//Maps//map "<<cmap<<".map";

FILE.open( ssaux.str().c_str() );

if( !FILE.is_open() ) return;

//NORMAL MAP

for( int i = 0; i < 14; i++ )
{
    for( int j = 0; j < 24; j++ )
    {
        FILE>>MAP_NORMAL_SKELETON[i][j];
        if( MAP_NORMAL_SKELETON[i][j] != -1 )
        MAP_NORMAL_TEX[i][j] = ASSETS.getTex_NORMAL( MAP_NORMAL_SKELETON[i][j] );
        else
        MAP_NORMAL_TEX[i][j] = NULL;
    }

}


//BACKGROUND MAP

for( int i = 0; i < 14; i++ )
{
    for( int j = 0; j < 24; j++ )
    {
        FILE>>MAP_BG_SKELETON[i][j];
        if( MAP_BG_SKELETON[i][j] != -1 )
        MAP_BG_TEX[i][j] = ASSETS.getTex_BG( MAP_BG_SKELETON[i][j] );
        else
        MAP_BG_TEX[i][j] = NULL;
    }


}

}
void CLS_MAP::replaceChunk_NORMAL( int x,int y,int nr ){
MAP_NORMAL_SKELETON[y][x] = nr;
if( nr != -1 )
MAP_NORMAL_TEX[y][x]      = ASSETS.getTex_NORMAL( nr );
else
    MAP_NORMAL_TEX[y][x] = NULL;
}
void CLS_MAP::replaceChunk_BG( int x,int y,int nr ){
MAP_BG_SKELETON[y][x] = nr;
if( nr != -1 )
MAP_BG_TEX[y][x]      = ASSETS.getTex_BG( nr );
else
    MAP_BG_TEX[y][x] = NULL;
}
void CLS_MAP::draw_NORMAL(){
int i,j;

// --- SHOW NORMAL GROUND ---

for( i = 0; i <14; i++ )
    for( j = 0; j< 24; j++ )
    {
        ApplyTex( j*80, i*80, MAP_NORMAL_TEX[i][j] );
    }

}
void CLS_MAP::draw_BG(){
int i,j;

// --- SHOW BACKGROUND ---

for( i = 0; i <14; i++ )
    for( j = 0; j< 24; j++ )
    {
        ApplyTex( j*80, i*80 +1, MAP_BG_TEX[i][j] );
    }

}
void CLS_MAP::LOAD_TEST(void){

load( 0 );

/*
int i;
for( i  = 0; i < 24; i++ )
{
    MAP_NORMAL_TEX[13][i] = ASSETS.getTex_NORMAL( 1 );
    MAP_NORMAL_SKELETON[13][i] = 1;
}

for( i  = 0; i < 24; i++ )
{
    MAP_NORMAL_TEX[12][i] = ASSETS.getTex_NORMAL( 0 );
    MAP_NORMAL_SKELETON[12][i] = 0;
}

*/
//MAP_NORMAL_TEX[6][6] = ASSETS.getTex( 5 );
}
void CLS_MAP::StreamMapToFile( std::ofstream *FILE ){

//NORMAL MAP

for( int i = 0; i < 14; i++ )
{
    for( int j = 0; j < 24; j++ )
        *FILE<<MAP_NORMAL_SKELETON[i][j]<<' ';

    *FILE<<"\n";
}

*FILE<<"\n";

//BACKGROUND MAP

for( int i = 0; i < 14; i++ )
{
    for( int j = 0; j < 24; j++ )
        *FILE<<MAP_BG_SKELETON[i][j]<<' ';

    *FILE<<"\n";
}

}
bool CLS_MAP::isCollision( int x, int y ){
if( MAP_NORMAL_SKELETON[y][x] == -1 ) return false;

return true;
}

