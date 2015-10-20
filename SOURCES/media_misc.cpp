#include "base.h"
#include "basics.h"
#include <iostream>
//COLOR
SDL_Color WHITE = { 255,255,255,255 };

//FONTS
TTF_Font *Font_Amber_20 = NULL;

void loadFonts(void){

Font_Amber_20 = TTF_OpenFont( "Data//Fonts//Amble-Regular.ttf",20 );

if( Font_Amber_20 == NULL )
    std::cout << "fail to load font!";

}


