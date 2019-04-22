//
// Created by chaed on 19. 1. 22.
//

#ifndef CONTROLLER_BORDER_H
#define CONTROLLER_BORDER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Controller.h"
#include "SDL2EasyGUI/include/ControllerBuilder.h"


namespace sdleasygui {

class BorderBuilder;
class Border : public Controller {

public:
    virtual ~Border() = default;
    explicit Border(ControllerBuilder &basic);

    virtual void onDraw() override;
    virtual void onDrawBackground() override;

protected:

    virtual void initialize() override;

private:

};

class BorderBuilder : public ControllerBuilder {
public:

    BorderBuilder(const GraphicInterface::window_type window, const TPoint &point, const std::string &str)
        : ControllerBuilder(window, point, str) {
    }

    BorderBuilder(const GraphicInterface::window_type window, TPoint &&point, std::string &&str)
        : ControllerBuilder(window, point, str) {
    }

    virtual ~BorderBuilder() = default;

    virtual Controller::controll_ptr build() {
        return new Border(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_TBORDER_H
