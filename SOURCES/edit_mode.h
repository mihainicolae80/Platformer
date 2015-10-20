#ifndef EDIT_MODE_H_INCLUDED
#define EDIT_MODE_H_INCLUDED

#include "base.h"
#include "basics.h"

enum{ DRAWMODE_NORMAL, DRAWMODE_BACKGROUND };

extern class CLS_EDIT_MODE{
private:


int SELECTED_ITEM,mouse_x,mouse_y,SELECTED_CHUNK_X,SELECTED_CHUNK_Y,FILE_NR_COUNT;

SDL_Texture *HIGHLIGHT_TEX,*TEXT_SAVE,*TEXT_LOAD,*TEXT_LINES,
            *BUTTON_NORMAL_TEX,*BUTTON_BG_TEX,*FILE_NR_TEX;

bool MOUSE_BUTTONDOWN_LEFT,MOUSE_BUTTONDOWN_RIGHT,SHOWLINES;


public:
int DRAW_MODE;

void init(void);
void draw_UI(void);
void save( void );
void load( void );
void giveEvent( SDL_Event *EVENT  );
void handleLogics( void );

}EDIT_MODE;

#endif // EDIT_MODE_H_INCLUDED
