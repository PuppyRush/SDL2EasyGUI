//
// Created by chaed on 19. 1. 22.
//

#ifndef GUI_GRAPHICINTERFACE_H
#define GUI_GRAPHICINTERFACE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SDL2EasyGUI/include/SEG_Window.h"
#include "SDL2EasyGUI/include/EventListener.h"
#include "../../include/EventQueue.h"

namespace sdleasygui {

class GraphicInterface : public EventListener {

public:
    using window_type = SEG_Window*;
    using unique_type = SEG_Window::unique_type ;

    virtual ~GraphicInterface();


    inline void setWindowTitle(const std::string& str) { m_window->setTitle(str);}
    inline void setWindowWidth(const t_size width) noexcept { m_window->setWidth(width);}
    inline void setWindowHeight(const t_size height) noexcept { m_window->setHeight(height);}
    inline const t_size getWindowWidth() const noexcept { return m_window->getWidth();}
    inline const t_size getWindowHeight() const noexcept { return m_window->getHeight();}

    inline TColor getBackgroundColor() const noexcept {
        return m_backgroundColor;
    }
    inline void setBackgroundColor(const TColor &background_color) noexcept {
        m_backgroundColor = background_color;
    }
    inline void setBackgroundColor(TColor &&background_color) noexcept {
        m_backgroundColor = background_color;
    }

    void setWindow(window_type window) { m_window = window; }
    window_type getWindow() const noexcept {  return m_window;  }

protected:

    window_type m_window = nullptr;

    GraphicInterface()
        :m_window()
    {}

    virtual void refresh() = 0;
    virtual void onDraw() = 0;
    virtual void onDrawBackground() = 0;

    virtual void _drawBackground(const SDL_Rect rect )
    {
        auto renderer = getWindow()->getSDLRenderer();

        const auto &back_color = getBackgroundColor();
        SDL_SetRenderDrawColor(renderer, back_color.r, back_color.g, back_color.b, 255);

        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
    }

    TColor m_backgroundColor;
};

class TextDrawer
{
    SDL_Surface* textSurface;
    SDL_Texture* texture;
public:

    TextDrawer(SDL_Renderer* renderer, const TFont& fontinfo, const std::string str)
        :textSurface(nullptr)
    {
        TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
        SDL_Color textColor = { fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, 0 };

        textSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    }
    ~TextDrawer()
    {
        SDL_FreeSurface(textSurface);
    }

    inline SDL_Texture* getTexture() { return texture;}
    inline SDL_Surface* getTextSurface() { return textSurface;}

    inline const double getTextWidth() { return static_cast<double>(textSurface->w);}
    inline const double getTextHeight() { return static_cast<double>(textSurface->h);}

};


}

#endif //TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H
