#include "edit_mode.h"
#include "assets.h"
#include "map.h"
#include <cmath>
#include <fstream>

void CLS_EDIT_MODE::init(){
SELECTED_ITEM = 0;
SELECTED_CHUNK_X = 0;
SELECTED_CHUNK_Y = 0;
SHOWLINES = false;
HIGHLIGHT_TEX = LoadTex( "Data//Sprites//EDITOR//highlight.png" );
MOUSE_BUTTONDOWN_LEFT  = false;
MOUSE_BUTTONDOWN_RIGHT = false;
TEXT_SAVE   = LoadTex( "Data//Sprites//EDITOR//text_save.png" );
TEXT_LOAD   = LoadTex( "Data//Sprites//EDITOR//text_load.png" );
TEXT_LINES  = LoadTex( "Data//Sprites//EDITOR//text_lines.png" );
BUTTON_NORMAL_TEX    = LoadTex( "Data//Sprites//EDITOR//BUTTON_NORMAL.png" );
BUTTON_BG_TEX        = LoadTex( "Data//Sprites//EDITOR//BUTTON_BG.png" );

//DRAW MODE BUTTONS
DRAW_MODE = DRAWMODE_NORMAL;
//Set the transparency
SDL_SetTextureAlphaMod( BUTTON_BG_TEX, 100 );

FILE_NR_COUNT = 0;
FILE_NR_TEX   = ENGINE_RenderText_Texture( Font_Amber_20, "MAP: 0", WHITE );

}
void CLS_EDIT_MODE::draw_UI(){
int i,shown = 0,w,h;
SDL_Rect box_draw;

SDL_SetRenderDrawColor( RENDERER_MAIN, 255,0,0,100 );

// Render RED lines
if( SHOWLINES )
{
    for( i = 0; i < 14; i++ )
    SDL_RenderDrawLine( RENDERER_MAIN,0,
                        i * 80 * SCALE + ( SCREEN_HEIGHT - (double)SCREEN_WIDTH/16*9 )/2
                        ,SCREEN_WIDTH,
                        i * 80 * SCALE + ( SCREEN_HEIGHT - (double)SCREEN_WIDTH/16*9 )/2
                        );

    for( i = 0; i < 24; i++ )
    SDL_RenderDrawLine( RENDERER_MAIN,
                        i * 80 * SCALE ,
                        0,
                        i * 80 * SCALE,
                        SCREEN_HEIGHT
                        );
}




//HIGHLIGHT SELECTED
if( DRAW_MODE == DRAWMODE_NORMAL )
    ApplyTex( SELECTED_CHUNK_X * 80, SELECTED_CHUNK_Y * 80, ASSETS.getTex_NORMAL( SELECTED_ITEM ) );
else
if( DRAW_MODE == DRAWMODE_BACKGROUND )
    ApplyTex( SELECTED_CHUNK_X * 80, SELECTED_CHUNK_Y * 80, ASSETS.getTex_BG( SELECTED_ITEM ) );

//Draw LEFT SIDE UI
if( !( mouse_x > 0 && mouse_x < 250 && mouse_y > 100 && mouse_y < 550 ) )
{


//RENDER --BG --
box_draw.x = 0;
box_draw.y = 100;
box_draw.w = 250;
box_draw.h = 450;

SDL_SetRenderDrawBlendMode( RENDERER_MAIN, SDL_BLENDMODE_BLEND );
SDL_SetRenderDrawColor( RENDERER_MAIN, 0,0,0,175 );
SDL_RenderFillRect( RENDERER_MAIN, &box_draw );


box_draw.y = 320;
box_draw.h = 60;
SDL_SetRenderDrawColor( RENDERER_MAIN, 0,0,0,200 );
SDL_RenderFillRect( RENDERER_MAIN, &box_draw );

//RENDER -- BUTTONS --
ApplyTex_straight(  40, 150,BUTTON_NORMAL_TEX );
ApplyTex_straight( 140, 150,BUTTON_BG_TEX );

//RENDER -- ITEMS --
shown = 0;

if( DRAW_MODE == DRAWMODE_NORMAL )
{
    for( i = SELECTED_ITEM - 2; i <= SELECTED_ITEM + 2; i++ )
    {
            shown ++;
        if( i >= -1 && i < MAXIMUM_NORMAL_TEX )
        {
            SDL_QueryTexture( ASSETS.getTex_NORMAL( i ),0,0,&w,&h );


            box_draw.x = (w - 80)/2;
            box_draw.y = (h - 80)/2;
            box_draw.w = 80;
            box_draw.h = 80;

            ApplyTex_straight( 30, 85 + (shown) * 80  , ASSETS.getTex_NORMAL( i ),&box_draw );
        }

    }
}
else
if( DRAW_MODE == DRAWMODE_BACKGROUND )
{
    for( i = SELECTED_ITEM - 2; i <= SELECTED_ITEM + 2; i++ )
    {
            shown ++;
        if( i >= -1 && i < MAXIMUM_BG_TEX )
        {
            SDL_QueryTexture( ASSETS.getTex_BG( i ),0,0,&w,&h );


            box_draw.x = (w - 80)/2;
            box_draw.y = (h - 80)/2;
            box_draw.w = 80;
            box_draw.h = 80;

            ApplyTex_straight( 30, 85 + (shown) * 80  , ASSETS.getTex_BG( i ),&box_draw );
        }

    }
}



}

//DRAW TEXTS
ApplyTex( SCREEN_WIDTH/100*30,50,TEXT_LINES );
ApplyTex( SCREEN_WIDTH/100*50,50,TEXT_SAVE );
ApplyTex( SCREEN_WIDTH/100*75,50,TEXT_LOAD );

ApplyTex( SCREEN_WIDTH/100*63,50,FILE_NR_TEX );

//Draw over mouse OOU
//ApplyTex_straight( mouse_x, mouse_y, ASSETS.getTex( SELECTED_ITEM ) );

}
void CLS_EDIT_MODE::giveEvent( SDL_Event *EVENT  ){

if( EVENT->type == SDL_MOUSEWHEEL )
{
    if( EVENT->wheel.y > 0 )
    {
        SELECTED_ITEM --;
        if( SELECTED_ITEM < -1 ) SELECTED_ITEM = -1;
    }
    else
    if( EVENT->wheel.y < 0 )
    {
        SELECTED_ITEM ++;
        if( SELECTED_ITEM > MAXIMUM_NORMAL_TEX - 1 ) SELECTED_ITEM = MAXIMUM_NORMAL_TEX -1;
    }
}
else
if( EVENT->type == SDL_MOUSEMOTION )
{
    mouse_x = EVENT->motion.x;
    mouse_y = EVENT->motion.y;

    SELECTED_CHUNK_X = floor( (double)mouse_x/SCALE/80 );
    SELECTED_CHUNK_Y = floor( (double)mouse_y/SCALE/80 );

}
else
if( EVENT->type == SDL_MOUSEBUTTONDOWN )
{
    if( EVENT->button.button == SDL_BUTTON_LEFT )
        MOUSE_BUTTONDOWN_LEFT = true;
    else
    if( EVENT->button.button == SDL_BUTTON_RIGHT )
        MOUSE_BUTTONDOWN_RIGHT = true;

}
else
if( EVENT->type == SDL_MOUSEBUTTONUP )
{
    if( EVENT->button.button == SDL_BUTTON_LEFT )
        MOUSE_BUTTONDOWN_LEFT = false;
    else
    if( EVENT->button.button == SDL_BUTTON_RIGHT )
        MOUSE_BUTTONDOWN_RIGHT = false;

}
else
if( EVENT->type == SDL_KEYDOWN )
{
    if( EVENT->key.keysym.scancode == SDL_SCANCODE_F5 )
        SHOWLINES = !SHOWLINES;
    else
    if( EVENT->key.keysym.scancode == SDL_SCANCODE_1 )
    {
        DRAW_MODE = DRAWMODE_NORMAL;

        SDL_SetTextureAlphaMod( BUTTON_NORMAL_TEX, 255 );
        SDL_SetTextureAlphaMod( BUTTON_BG_TEX, 100 );
    }
    else
    if( EVENT->key.keysym.scancode == SDL_SCANCODE_2 )
    {
        DRAW_MODE = DRAWMODE_BACKGROUND;

        SDL_SetTextureAlphaMod( BUTTON_NORMAL_TEX, 100 );
        SDL_SetTextureAlphaMod( BUTTON_BG_TEX, 255 );
    }
    else
    if( EVENT->key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET )
    {
        stringstream ssaux;
        FILE_NR_COUNT -- ;
        if( FILE_NR_COUNT < 0 ) FILE_NR_COUNT = 0;

        //update tex
        ssaux<<"MAP: "<<FILE_NR_COUNT;

        ENGINE_DestroyTexture( &FILE_NR_TEX );
        FILE_NR_TEX = ENGINE_RenderText_Texture( Font_Amber_20,ssaux.str().c_str() , WHITE );
    }
    else
    if( EVENT->key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET )
    {
        stringstream ssaux;

        FILE_NR_COUNT ++ ;

        //update tex
        ssaux<<"MAP: "<<FILE_NR_COUNT;

        ENGINE_DestroyTexture( &FILE_NR_TEX );
        FILE_NR_TEX = ENGINE_RenderText_Texture( Font_Amber_20,ssaux.str().c_str() , WHITE );
    }
    else
    if( EVENT->key.keysym.scancode == SDL_SCANCODE_F7)
    {
        save();
    }
    else
    if( EVENT->key.keysym.scancode == SDL_SCANCODE_F8)
    {
        MAP.load( FILE_NR_COUNT );
    }

}
}
void CLS_EDIT_MODE::handleLogics(){

if( MOUSE_BUTTONDOWN_LEFT )
{
    if( DRAW_MODE == DRAWMODE_NORMAL )
    MAP.replaceChunk_NORMAL( SELECTED_CHUNK_X, SELECTED_CHUNK_Y, SELECTED_ITEM );
    else
    if( DRAW_MODE == DRAWMODE_BACKGROUND )
    MAP.replaceChunk_BG( SELECTED_CHUNK_X, SELECTED_CHUNK_Y, SELECTED_ITEM );

}


}
void CLS_EDIT_MODE::save(){
std::ofstream FILE;
stringstream filename;

filename <<"Data//Maps//map "<<FILE_NR_COUNT<<".map";

FILE.open( filename.str().c_str() );

MAP.StreamMapToFile( &FILE );

FILE.close();

}






