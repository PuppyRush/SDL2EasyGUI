//
// Created by chaed on 18. 12. 27.
//

#include "ButtonBasic.h"

using namespace sdleasygui;

ButtonBasic::ButtonBasic(ControllBuilder& bld)
    :Border(bld)
{


}


void ButtonBasic::onDraw()
{
    _drawCarot();
    Border::onDraw();
}

void ButtonBasic::onDrawBackground()
{
    auto renderer = getWindow()->getSDLRenderer();

    SDL_Rect rect;
    if(getAutoSize())
        rect = SDL_Rect{ getPoint().x-20,
                         getPoint().y,
                         static_cast<int>(m_textWidth*1.2),
                         static_cast<int>(m_textHeight*1.4)};
    else
        rect = SDL_Rect{ getPoint().x, getPoint().y, getWidth(), getHeight()};

    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick()*2)+1;
    rect.w = (rect.w - getBorderThick()*2)+1;

    drawBackground(rect, getBackgroundColor());

    SDL_Rect renderQuad = { static_cast<int>(getPoint().x + ( getWidth() - m_textWidth)/2)
        , static_cast<int>(getPoint().y + ( getHeight() - m_textHeight)/2)
        , static_cast<int>(m_textWidth)
        , static_cast<int>(m_textHeight) };
    SDL_RenderCopy(renderer, m_texture.get(), nullptr, &renderQuad);
}

void ButtonBasic::initialize()
{
    auto renderer = getWindow()->getSDLRenderer();
    const auto& fontinfo = getFont();
    TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
    std::string score_text = getName();
    SDL_Color textColor = { fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, 0 };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);

    auto texture_deleter = [](SDL_Texture* texture) {
      if(texture==nullptr) delete texture;
    };

    m_texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, textSurface),texture_deleter);
    SDL_FreeSurface(textSurface);

    m_textWidth = textSurface->w;
    m_textHeight = textSurface->h;


    Border::initialize();
}
void ButtonBasic::_drawCarot()
{
    auto renderer = getWindow()->getSDLRenderer();

    if(isSelected() && isCarot())
    {
        if( GroupControllManager::getInstance().isSelected(getGroup(), getResourceId()))
        {
            SDL_Rect rect{getPoint().x-5, getPoint().y-5, getWidth()+10, getHeight()+10};

            const auto& linecolor = TColor::getColor(ColorCode::red);
            SDL_SetRenderDrawColor(renderer, linecolor.r, linecolor.g, linecolor.b, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
