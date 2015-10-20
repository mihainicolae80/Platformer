#include <SDL2/SDL.h>
#include "base.h"
#include "rungame.h"
#include "player.h"
#include "map.h"
#include "settings.h"

int main(){

SETTINGS.load();

init_Engine();

PLAYER_1.init();

MAP.LOAD_TEST();

RUN_GAME();

TTF_Quit();
SDL_Quit();

return 0;
}
