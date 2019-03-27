//
// Created by chaed on 19. 2. 10.
//

#ifndef SDLEASYGUIDE_QUIT_H
#define SDLEASYGUIDE_QUIT_H

#include <SDL2/SDL.h>

#include "Windows/DisplayController.h"

namespace sdleasygui {

void SDLEasyGUI_Quit() {
    DisplayController::getInstance().finish();
    SDL_Quit();
}

}

#endif //TETRIS_FIGURE_CLASS_SEG_QUIT_H
