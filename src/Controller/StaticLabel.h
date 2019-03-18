//
// Created by chaed on 18. 12. 26.
//

#ifndef CONTROLLER_STATICLABEL_H
#define CONTROLLER_STATICLABEL_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Border.h"

namespace sdleasygui {

typedef struct StaticLabelBasic : public ControllBasic {
}StaticLabelBasic;

class StaticLabelBuilder;
class StaticLabel : public Border {

public:
    virtual ~StaticLabel() = default;
    explicit StaticLabel(StaticLabelBuilder &bld);

    virtual void onDraw() override final;
    virtual void initialize() override final;

};

class StaticLabelBuilder : public ControllBuilder {
public:

    StaticLabelBuilder(const GraphicInterface::window_type window, const TPoint &point, const std::string &str)
        : ControllBuilder(window, point, str) {
    }

    StaticLabelBuilder(const GraphicInterface::window_type window, TPoint &&point, std::string &&str)
        : ControllBuilder(window, point, str) {
    }

    virtual ~StaticLabelBuilder() = default;

    virtual Controll::controll_ptr build() final {
        return new StaticLabel(*this);
    }

    StaticLabelBasic m_borderBasic;

};

}

#endif //TETRIS_FIGURE_CLASS_TSTATICLABEL_H
