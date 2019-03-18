//
// Created by chaed on 18. 12. 27.
//

#include "RadioButton.h"

using namespace sdleasygui;

RadioButton::RadioButton(ControllBuilder& bld)
    :ButtonBasic(bld)
{
    bld.kind(ControllKind::StaticLabel);
}


void RadioButton::initialize()
{
    Controll::initialize();
}

void RadioButton::onDraw()
{
    ButtonBasic:onDraw();
}
