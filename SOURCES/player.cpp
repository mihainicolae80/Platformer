#include "player.h"
#include "base.h"
#include <cmath>
#include "map.h"

#define movement_speed 10
#define MAXIMUM_JUMP_SPEED 20
#define START_FALLING_SPEED 15
#define GRAVITY_VELOCITY 2

CLS_PLAYER PLAYER_1;

void CLS_PLAYER::init(){

BODY_R.x = 300;
BODY_R.y = 500;
BODY_R.w = 80;
BODY_R.h = 160;

_skin = NULL;
_skin = LoadTex( "Data//Sprites//SKINS//HERO//move.png" );
vely = 0;
IS_JUMPING = false;
JUMP_TIMER = SDL_GetTicks();
JUMP_DELAY_TIMER = SDL_GetTicks() - 2000;
IS_FALLING = false;
}
void CLS_PLAYER::draw(){


ApplyTex( BODY_R.x,BODY_R.y, _skin );

}
void CLS_PLAYER::handleKeys(void){
//int block_x,block_y;
bool COLLIDED_DOWN = false;
const unsigned char *KEYPRESSED = SDL_GetKeyboardState(NULL);

velx = 0;


if( KEYPRESSED[ SDL_SCANCODE_RIGHT ] )
{
    velx += movement_speed;
}
else
if( KEYPRESSED[ SDL_SCANCODE_LEFT ] )
{
    velx -= movement_speed;
}

if( KEYPRESSED[ SDL_SCANCODE_UP ] )
{
    if( IS_JUMPING == false && IS_FALLING == false && SDL_GetTicks() - JUMP_DELAY_TIMER > 450 )
    {
        IS_JUMPING = true;
        vely = -MAXIMUM_JUMP_SPEED;
        JUMP_TIMER = SDL_GetTicks();
        JUMP_DELAY_TIMER = SDL_GetTicks();
    }
}
else
if( KEYPRESSED[ SDL_SCANCODE_DOWN ] )
{
    //vely += movement_speed;
}

if( IS_JUMPING )
{
    if( SDL_GetTicks() - 10 > JUMP_TIMER )
    {
        vely += GRAVITY_VELOCITY;

        JUMP_TIMER = SDL_GetTicks();
    }

    if( vely > 0 )
    {
        IS_JUMPING = false;
        IS_FALLING = true;
    }
}

if( IS_FALLING )
{
    if( SDL_GetTicks() - 20 > JUMP_TIMER )
    {
        vely = START_FALLING_SPEED;

        JUMP_TIMER = SDL_GetTicks();
    }
}



/// --- Check Collision (FORESEE) ---
//block_x = floor( (double)BODY_R.x / 80 );
//block_y = floor( (double)BODY_R.y / 80 );

for( int x = 0; x < 24; x++ )
    for( int y = 0; y < 14; y++ )
{
    if( MAP.isCollision( x,y ) )
    {
        #define m_x x * 80
        #define m_y y * 80
        #define m_w 80
        #define m_h 80

        #define p_x BODY_R.x + velx
        #define p_y BODY_R.y + vely
        #define p_w BODY_R.w
        #define p_h BODY_R.h

        #define mc_x x * 80 + 80/2
        #define mc_y y * 80 + 80/2

        #define pc_x BODY_R.x + BODY_R.w/2
        #define pc_y BODY_R.y + BODY_R.h/2

        //PLAYED COLLIDES WITH ENVIROMENT
        if( p_x + p_w > m_x && p_x < m_x + m_w &&
            p_y + p_h > m_y && p_y < m_y + m_h  )
        {


            //COLLISION: RIGHT
            if( p_x + p_w > m_x && ( p_y < m_y + m_h && p_y + p_h > m_y )
                &&!( p_x - velx < m_x + m_w )
                )
            {
                //stop MOVEMENT
                velx = 0;

                CONS.out( "collided right" );

                //REPOSITION
                BODY_R.x = m_x - BODY_R.w;
            }
            /*
            else
            //COLLISION: LEFT
            if( p_x < m_x + m_w &&
                ( p_y < m_y + m_h && p_y + p_h > m_y ) &&
                !( p_x - velx < m_x + m_w )
                 ) //m_y + 20 < p_y + p_h
            {
                //stom MOVEMENT
                velx = 0;

                    CONS.out( "collided left" );

                //REPOSITION
                //BODY_R.x = m_x + m_w +5;
            }
            */
            //COLLISION: DOWN
            if( p_y + p_h < mc_y )
            {
                COLLIDED_DOWN = true;

                if( IS_FALLING )
                {
                    //Stop FALLING
                    IS_FALLING = false;
                    vely = 0;

                    //REPOSITION
                    BODY_R.y = m_y - p_h;
                }
            }
        }


    }
}

//Start FALLING
if( !COLLIDED_DOWN )
{
    IS_FALLING = true;

}


BODY_R.x += velx;
BODY_R.y += vely;
}




