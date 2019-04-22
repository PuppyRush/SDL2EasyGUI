//
// Created by chaed on 18. 12. 26.
//

#ifndef CONTROLLER_STATICLABEL_H
#define CONTROLLER_STATICLABEL_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "LabelBasic.h"

namespace sdleasygui {

typedef struct StaticLabelBasic : public ControllerBasic {
}StaticLabelBasic;

class StaticLabelBuilder;
class StaticLabel : public LabelBasic {

public:
    virtual ~StaticLabel() = default;
    explicit StaticLabel(StaticLabelBuilder &bld);


protected:
    virtual void onDrawBackground() override;
    virtual void onDraw() override final;
    virtual void initialize() override final;
};

class StaticLabelBuilder : public ControllerBuilder {
public:

    StaticLabelBuilder(const GraphicInterface::window_type window, const TPoint &point, const std::string &str)
        : ControllerBuilder(window, point, str) {
    }

    StaticLabelBuilder(const GraphicInterface::window_type window, TPoint &&point, std::string &&str)
        : ControllerBuilder(window, point, str) {
    }

    virtual ~StaticLabelBuilder() = default;

    virtual Controller::controll_ptr build() final {
        return new StaticLabel(*this);
    }

    StaticLabelBasic m_borderBasic;

};

}

#endif //TETRIS_FIGURE_CLASS_TSTATICLABEL_H
