#ifndef ASSETS__H_INCLUDED
#define ASSETS__H_INCLUDED

#include "base.h"
#include <sstream>

#define MAXIMUM_NORMAL_TEX 100
#define MAXIMUM_BG_TEX 100

extern class CLS_ASSETS{
private:
SDL_Texture *_NULL_TEX,*NORMAL_TEX[ MAXIMUM_NORMAL_TEX ],*BG_TEX[ MAXIMUM_BG_TEX ];
public:
void init(void);
SDL_Texture* getTex_NORMAL( int x );
SDL_Texture* getTex_BG( int x );
}ASSETS;

#endif // ASSETS__H_INCLUDED
