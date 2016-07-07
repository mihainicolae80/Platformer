#include "console.h"

void CLS_CONSOLE::init(){

// -- INIT GENERAL --
_DISPLAY = false;


//  -- INIT LIST --
_First_node = new node;
_Last_node  = new node;
_First_node->next = _Last_node;
_Last_node->next  = NULL;

//Init Font
CONS_FONT = TTF_OpenFont( "Data//Fonts//Amble-Regular.ttf",24 );

INPUT_LINE_TEX = NULL;
INPUT_LINE_TEXT[0] = '\0';

firstline    = 0;
item_counter = 0;

}
void CLS_CONSOLE::draw(){
//Close if needed
if( !_DISPLAY ) return;
int i,shown = 0;

//Render the background
SDL_Rect box_bg;
box_bg.x    =   0;
box_bg.y    =   0;
box_bg.w    =   SCREEN_WIDTH;
box_bg.h    =   SCREEN_HEIGHT*30/100;

SDL_SetRenderDrawColor    ( RENDERER_MAIN, 0,0,0,100 );
SDL_SetRenderDrawBlendMode( RENDERER_MAIN, SDL_BLENDMODE_BLEND );

SDL_RenderFillRect( RENDERER_MAIN, &box_bg );

//INPUT LINE Background
box_bg.y    =   SCREEN_HEIGHT*30/100;
box_bg.h    =   20;

SDL_SetRenderDrawColor    ( RENDERER_MAIN, 0,0,0,175 );
SDL_SetRenderDrawBlendMode( RENDERER_MAIN, SDL_BLENDMODE_BLEND );

SDL_RenderFillRect( RENDERER_MAIN, &box_bg );


//Render CONTENT
shown = 0;
i     = 1;
for( node *inode = _First_node->next; inode != _Last_node && shown < 20 ;inode = inode->next , i++ )
{
    if( i > firstline )
    {
        shown++;

        ApplyTex_straight( 5, SCREEN_HEIGHT*30/100 - shown * 25*SCALE,inode->tx_text );
    }
}


//RENDER INPUT LINE TEXT
ApplyTex_straight( 10,SCREEN_HEIGHT*30/100, INPUT_LINE_TEX );

}
void CLS_CONSOLE::switch_if_display(){

/*
-When shown:
    *the game is paused
    *all the imput goes the the console
-When close
    *the game is resumed
*/

_DISPLAY = !_DISPLAY;

if( _DISPLAY )
    SDL_StartTextInput();
else
    SDL_StopTextInput();


}
bool CLS_CONSOLE::is_shown(){
return _DISPLAY;
}
void CLS_CONSOLE::out( std::string text ){
item_counter ++;
//Create New Item
node* newnode = new node;
newnode->next = _First_node->next;
_First_node->next = newnode;
newnode->tx_text = ENGINE_RenderText_Texture( CONS_FONT, text.c_str() , WHITE );

}
void CLS_CONSOLE::sendEvent( SDL_Event *event ){

//reset update checker
bool INPUT_LINE_UPDATE = false;

//Add @Input to @String
if( event->type == SDL_TEXTINPUT && event->text.text[0] != '`' )
{
    GAME_strcat( INPUT_LINE_TEXT,event->text.text );

    INPUT_LINE_UPDATE = true;
}
else
if( event->type == SDL_KEYDOWN )
{
    if( event->key.keysym.scancode == SDL_SCANCODE_RETURN )
    {
        #define SET_UNKNOWN GAME_strcat( INPUT_LINE_TEXT," (X)" );
            string CTStr[10];
            int cstr = 0;
            for( unsigned int i = 0; i < SDL_strlen( INPUT_LINE_TEXT );i++ )
            if( INPUT_LINE_TEXT[i] == ' ' ) cstr++;
            else
            CTStr[cstr] += INPUT_LINE_TEXT[i];




            ///Switch Command
            if( CTStr[0] == "exit" )
            {

            }
            else
            if( CTStr[0] == "vp" )
            {
                if( CTStr[1] == "x" )
                {
                    VIEWPORT_x = atoi( CTStr[2].c_str() );
                }
                else
                if( CTStr[1] == "y" )
                {
                    VIEWPORT_y = atoi( CTStr[2].c_str() );
                }
                else
                SET_UNKNOWN;
            }
            else
            SET_UNKNOWN;


            //Oputput
            out( INPUT_LINE_TEXT );

            //Erase String
            INPUT_LINE_TEXT[0] = '\0';
    }
    else
    if( event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE )
    {
        INPUT_LINE_TEXT[ SDL_strlen( INPUT_LINE_TEXT ) - 1 ] = '\0';
    }
    else
    if( event->key.keysym.scancode == SDL_SCANCODE_END )
        firstline = 0;
    if( event->key.keysym.scancode == SDL_SCANCODE_HOME )
    {
        firstline = item_counter - 12;
        if( firstline < 0 )  firstline = 0;
    }

    INPUT_LINE_UPDATE = true;
}
else
if( event->type == SDL_MOUSEWHEEL )
{
    if( event->wheel.y > 0 )
    {
        firstline ++;
    }
    else
    if( event->wheel.y < 0 )
    {
        firstline --;
        if( firstline < 0 ) firstline = 0;
    }
}

if( INPUT_LINE_UPDATE )
{
    ENGINE_DestroyTexture( &INPUT_LINE_TEX );
    INPUT_LINE_TEX = ENGINE_RenderText_Texture( CONS_FONT,INPUT_LINE_TEXT,WHITE );
    INPUT_LINE_UPDATE = false;
}


}
