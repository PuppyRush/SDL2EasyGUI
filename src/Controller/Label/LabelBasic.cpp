//
// Created by chaed on 19. 3. 31.
//

#include "LabelBasic.h"

using namespace sdleasygui;

LabelBasic::LabelBasic(ControllerBuilder& bld)
    :Border(bld)
{

}

void LabelBasic::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();
    TextDrawer textDrawer{renderer, getFont(), m_labelString};
    auto textSurface = textDrawer.getTextSurface();

    if(textSurface)
    {
        auto texture = textDrawer.getTexture();

        m_textWidth = textDrawer.getTextWidth();
        m_textHeight = textDrawer.getTextHeight();

        const auto point = getPoint();
        SDL_Rect renderQuad = { static_cast<int>(point.x +5)
            , static_cast<int>(point.y + ( getHeight() - m_textHeight)/2)
            , static_cast<int>(m_textWidth)
            , static_cast<int>(m_textHeight) };
        SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    }

    Border::onDraw();
}

void LabelBasic::onDrawBackground()
{


    Border::onDrawBackground();
}
