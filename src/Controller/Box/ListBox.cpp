//
// Created by chaed on 19. 2. 16.
//

#include "ListBox.h"

using namespace sdleasygui;

ListBox::ListBox(ListBoxBuilder &bld)
    :BoxBasic(bld)
{
    bld.kind(ControllerKind::ListBox);
}


void ListBox::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    TPoint accuPoint = getPoint();

    for(const item_ptr item : m_items)
    {
        TextDrawer textDrawer{renderer, getFont(), item->getString()};
        auto textSurface = textDrawer.getTextSurface();

        if(textSurface != nullptr) {
            auto texture = textDrawer.getTexture();
            const double text_width = static_cast<double>(textSurface->w);
            const double text_height = static_cast<double>(textSurface->h);

            const auto point = getPoint();
            SDL_Rect renderQuad =
                {static_cast<int>(accuPoint.x + 5), static_cast<int>(accuPoint.y), static_cast<int>(text_width),
                 static_cast<int>(text_height)};
            SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

            accuPoint.y += text_height + 3;
        }
    }

    Border::onDraw();
}