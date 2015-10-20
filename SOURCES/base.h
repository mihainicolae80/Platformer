#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// -- FROM CLASSES --
#include "console.h"

//---WINDOWS AND RENDERES---
extern SDL_Window   *WINDOW_MAIN;
extern SDL_Renderer *RENDERER_MAIN;

// --Screen --
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

//ViewPorts
extern int VIEWPORT_x;
extern int VIEWPORT_y;

int init_Engine(void);
void handleEvent_resizeWindow( SDL_Event *EVENT );

#endif // BASE_H_INCLUDED
