//
// Created by chaed on 19. 3. 8.
//

#ifndef TETRIS_FIGURE_CLASS_COMBOBOX_H
#define TETRIS_FIGURE_CLASS_COMBOBOX_H

#include "BoxBasic.h"

namespace sdleasygui {

class ComboBox : public BoxBasic{

public:
    ComboBox(BorderBuilder& bld);
    virtual ~ComboBox() = default;

};

}

#endif //TETRIS_FIGURE_CLASS_COMBOBOX_H
