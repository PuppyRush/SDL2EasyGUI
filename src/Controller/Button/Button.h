//
// Created by chaed on 18. 12. 27.
//

#ifndef CONTROLLER_BUTTON_H
#define CONTROLLER_BUTTON_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "ButtonBasic.h"

namespace sdleasygui {

class ButtonBuilder;
class Button : public ButtonBasic {

public:
    explicit Button(ButtonBuilder &bld);
    virtual ~Button() = default;

    virtual void initialize() override;
    virtual void onDraw() override;
    virtual void onDrawBackground() override;

};

class ButtonBuilder : public BorderBuilder {
public:

    ButtonBuilder(const GraphicInterface::window_type window, const TPoint &point, const std::string &str)
        : BorderBuilder(window, point, str) {
    }

    ButtonBuilder(const GraphicInterface::window_type window, TPoint &&point, std::string &&str)
        : BorderBuilder(window, point, str) {
    }

    virtual ~ButtonBuilder() = default;

    virtual Controller::controll_ptr build() final {
        return new Button(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_TBUTTON_H
