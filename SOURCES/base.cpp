#include "base.h"
#include "map.h"
#include "assets.h"
#include "edit_mode.h"
#include "media_misc.h"
#include "settings.h"

///--- Declaration ---
SDL_Window   *WINDOW_MAIN     = NULL;
SDL_Renderer *RENDERER_MAIN   = NULL;

// --Screen --
int SCREEN_WIDTH  = 1280;
int SCREEN_HEIGHT = 720;//720;

//ViewPorts
int VIEWPORT_x = 0;
int VIEWPORT_y = 0;

/// -- CLASSES --
CLS_CONSOLE     CONS;
CLS_MAP         MAP;
CLS_ASSETS      ASSETS;
CLS_EDIT_MODE   EDIT_MODE;


/// --- FUNCTIONS ---
int init_Engine(){
int flags;

//Init SDL
if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    return 1;
//Init TTF
if( TTF_Init() == -1 )
    return 2;

flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

if( SETTINGS.getFullScreen() )
    flags |= SDL_WINDOW_FULLSCREEN;

//Create Windows
WINDOW_MAIN = SDL_CreateWindow( "GAME PROJECT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                SETTINGS.getScreenWidth(), SETTINGS.getScreenHeight(),
                                flags );//| SDL_WINDOW_FULLSCREEN
if( WINDOW_MAIN == NULL )
    return 3;

//Create Renderer
RENDERER_MAIN = SDL_CreateRenderer( WINDOW_MAIN, 0,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
if( RENDERER_MAIN == NULL )
    return 4;

//Set Hints
SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" + SETTINGS.getRenderScaleQuality() );//"1"

//Init Fonts
loadFonts();

// -- INIT CLASSES --
CONS      .init();
ASSETS    .init();
MAP       .init();
EDIT_MODE .init();

return 0;
}
void handleEvent_resizeWindow( SDL_Event *EVENT ){

    if( EVENT->type         == SDL_WINDOWEVENT &&
        EVENT->window.event == SDL_WINDOWEVENT_RESIZED )
    {
        SDL_GetWindowSize( WINDOW_MAIN, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    }
}





