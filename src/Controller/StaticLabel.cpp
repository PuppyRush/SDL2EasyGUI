//
// Created by chaed on 18. 12. 26.
//

#include "StaticLabel.h"

using namespace sdleasygui;

StaticLabel::StaticLabel(StaticLabelBuilder& bld)
    :Border(bld)
{
    bld.kind(ControllKind::StaticLabel);
}

void StaticLabel::onDraw()
{
    Border::onDraw();
}

void StaticLabel::initialize()
{
    Border::initialize();
}

