//
// Created by chaed on 18. 12. 27.
//

#include "Button.h"

using namespace sdleasygui;

Button::Button(ButtonBuilder& bld)
    :ButtonBasic(bld)
{
    bld.kind(ControllerKind::Button);
}

void Button::onDrawBackground()
{
    ButtonBasic::onDrawBackground();
}

void Button::onDraw()
{
    ButtonBasic::onDraw();
}

void Button::initialize()
{
    ButtonBasic::initialize();
}

