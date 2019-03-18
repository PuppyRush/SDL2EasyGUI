//
// Created by chaed on 19. 1. 22.
//

#ifndef CONTROLLER_BORDER_H
#define CONTROLLER_BORDER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Controll.h"
#include "ControllBuilder.h"

namespace sdleasygui {

class BorderBuilder;
class Border : public Controll {

public:
    virtual ~Border() = default;
    explicit Border(ControllBuilder &basic);

    virtual void onDraw() override;
    virtual void onDrawBackground() {}

protected:

    virtual void initialize() override;

private:

};

class BorderBuilder : public ControllBuilder {
public:

    BorderBuilder(const GraphicInterface::window_type window, const TPoint &point, const std::string &str)
        : ControllBuilder(window, point, str) {
    }

    BorderBuilder(const GraphicInterface::window_type window, TPoint &&point, std::string &&str)
        : ControllBuilder(window, point, str) {
    }

    virtual ~BorderBuilder() = default;

    virtual Controll::controll_ptr build() {
        return new Border(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_TBORDER_H
