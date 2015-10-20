#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED



#include "basics.h"
#include <fstream>

/*
    -The default size of @PHISICAL bloc is 80x80 pixels
*/

extern class CLS_MAP{
private:
int MAP_NORMAL_SKELETON[14][24],MAP_BG_SKELETON[14][24];
SDL_Texture* MAP_NORMAL_TEX[14][24],*MAP_BG_TEX[14][24];

public:
void init(void);
void load(int cmap);
void replaceChunk_NORMAL( int x,int y,int nr );
void replaceChunk_BG    ( int x,int y,int nr );
bool isCollision( int x, int y );
void LOAD_TEST(void);
void draw_NORMAL(void);
void draw_BG(void);
void StreamMapToFile( std::ofstream *FILE );
}MAP;

#endif // MAP_H_INCLUDED
