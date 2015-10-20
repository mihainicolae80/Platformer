#include "settings.h"

CLS_SETTINGS SETTINGS;

void CLS_SETTINGS::load(){
std::ifstream infile( "settings.txt" );
std::string saux;

infile >> saux >> _screen_width;
infile >> saux >> _screen_height;
infile >> saux >> _fullscreen;
infile >> saux >> _render_scalequality;

infile.close();

}

int CLS_SETTINGS::getScreenWidth(){
return _screen_width;
}
int CLS_SETTINGS::getScreenHeight(){
return _screen_height;
}
bool CLS_SETTINGS::getFullScreen(){
return _fullscreen;
}
int CLS_SETTINGS::getRenderScaleQuality(){
return _render_scalequality;
}
