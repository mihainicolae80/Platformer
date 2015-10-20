#include "rungame.h"
#include "base.h"
#include "player.h"
#include "map.h"
#include "edit_mode.h"


void RUN_GAME(void){
SDL_Event EVENT;
bool RUN = true,IN_EDIT_MODE = true;
SDL_Texture *TEMPBG = NULL;


///--- INIT ---

/// -- INIT(temp) --
TEMPBG  = LoadTex( "Data//Sprites//background.png" );



/// -- MAIN LOOP --
while( RUN ){

/// -- EVENTS --
while( SDL_PollEvent( &EVENT ) )
{
    //Handles
    handleEvent_resizeWindow( &EVENT );

    if( CONS.is_shown() )
    CONS.sendEvent( &EVENT );
    else
    if( IN_EDIT_MODE )
    EDIT_MODE.giveEvent( &EVENT );

    if( EVENT.type == SDL_QUIT )
        RUN = false;
    else
    if( EVENT.type == SDL_KEYDOWN )
    {
        if( EVENT.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
        {
            RUN = false;
        }
        else
        if( EVENT.key.keysym.scancode == SDL_SCANCODE_GRAVE )
        {
            CONS.switch_if_display();
        }
        else
        if( EVENT.key.keysym.scancode == SDL_SCANCODE_F1 )
        {
            IN_EDIT_MODE = !IN_EDIT_MODE;
        }
    }

}

/// -- LOGICS --
PLAYER_1.handleKeys();

if( IN_EDIT_MODE )                EDIT_MODE.handleLogics();


/// -- RENDER --
SDL_SetRenderDrawColor( RENDERER_MAIN, 100,0,0,255 );
SDL_RenderClear( RENDERER_MAIN );

ApplyTex( 0,0, TEMPBG );


MAP.draw_BG();
MAP.draw_NORMAL();


PLAYER_1.draw();

if( IN_EDIT_MODE )               EDIT_MODE.draw_UI();

CONS.draw();

SDL_RenderPresent( RENDERER_MAIN );
}

}
