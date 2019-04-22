//
// Created by chaed on 18. 12. 26.
//

#include "StaticLabel.h"

using namespace sdleasygui;

StaticLabel::StaticLabel(StaticLabelBuilder& bld)
    :LabelBasic(bld)
{
    bld.kind(ControllerKind::StaticLabel);
    m_labelString = bld.getBasic().name;
}

void StaticLabel::onDraw()
{
    LabelBasic::onDraw();
}

void StaticLabel::onDrawBackground()
{

    LabelBasic::onDrawBackground();
}

void StaticLabel::initialize()
{
    auto renderer = getWindow()->getSDLRenderer();
    TextDrawer textDrawer{renderer, getFont(), m_labelString};
    auto textSurface = textDrawer.getTextSurface();

    if(textSurface) {
        auto texture = textDrawer.getTexture();

        m_textWidth = static_cast<double>(textSurface->w);
        m_textHeight = static_cast<double>(textSurface->h);

        getBasic()->height = m_textHeight;
        getBasic()->width = m_textWidth;
    }
    LabelBasic::initialize();
}
