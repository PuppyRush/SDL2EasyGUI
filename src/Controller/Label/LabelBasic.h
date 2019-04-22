//
// Created by chaed on 19. 3. 31.
//

#ifndef PROJECT_LABELBASIC_H
#define PROJECT_LABELBASIC_H

#include <string>

#include "../Border.h"

namespace sdleasygui {

class LabelBasic : public Border {

public:
    LabelBasic(ControllerBuilder& bld);
    virtual ~LabelBasic(){}

    std::string getString() { return m_labelString;}

protected:

    void onDraw();
    void onDrawBackground();

    int m_textWidth = 0;
    int m_textHeight = 0;
    std::shared_ptr<SDL_Texture> m_texture;
    std::string m_labelString;
};

}

#endif //PROJECT_LABELBASIC_H
