//
// Created by chaed on 18. 12. 27.
//

#include "RadioButton.h"

using namespace sdleasygui;

RadioButton::RadioButton(ControllerBuilder& bld)
    :ButtonBasic(bld)
{
    bld.kind(ControllerKind::StaticLabel);
}


void RadioButton::initialize()
{
    Controller::initialize();
}

void RadioButton::onDraw()
{
    ButtonBasic:onDraw();
}
