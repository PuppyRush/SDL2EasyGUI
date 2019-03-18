//
// Created by chaed on 18. 12. 27.
//

#ifndef CONTROLLER_BUTTONBASIC_H
#define CONTROLLER_BUTTONBASIC_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Border.h"

namespace sdleasygui {

class ButtonBasic : public Border {
public:

    virtual ~ButtonBasic() = default;

    inline const bool isMultiselected() const noexcept {
        Controll::isMultiselected();
    }
    inline void setMultiselected(bool multiselected) noexcept {
        Controll::setMultiselected(multiselected);
    }

    virtual void onDraw() override;
    virtual void onDrawBackground() override;

protected:
    explicit ButtonBasic(ControllBuilder &bld);
    virtual void initialize() override;

private:

    void _drawCarot();

    int m_textWidth = 0;
    int m_textHeight = 0;
    std::shared_ptr<SDL_Texture> m_texture;
};

}

#endif //TETRIS_FIGURE_CLASS_TBUTTONBASIC_H
