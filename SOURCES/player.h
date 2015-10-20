#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "basics.h"


extern class CLS_PLAYER{
private:
SDL_Rect BODY_R;
SDL_Texture *_skin;
int velx,vely;
bool IS_JUMPING,IS_FALLING;
Uint32 JUMP_TIMER,JUMP_DELAY_TIMER;
public:
void init(void);
void draw(void);
void handleKeys(void);

}PLAYER_1;

#endif // PLAYER_H_INCLUDED
