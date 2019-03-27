//
// Created by chaed on 19. 1. 22.
//

#ifndef GUI_GRAPHICINTERFACE_H
#define GUI_GRAPHICINTERFACE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "SEG_Window.h"
#include "EventListener.h"
#include "EventDelivery.h"


namespace sdleasygui {

class GraphicInterface : public EventListener, public EventDelivery {

public:
    using window_type = SEG_Window*;
    using unique_type = SEG_Window::unique_type ;

    virtual ~GraphicInterface();
    virtual void onDraw() = 0;

    inline void setWindowTitle(const std::string& str) { m_window->setTitle(str);}
    inline void setWindowWidth(const t_size width) noexcept { m_window->setWidth(width);}
    inline void setWindowHeight(const t_size height) noexcept { m_window->setHeight(height);}
    inline const t_size getWindowWidth() const noexcept { return m_window->getWidth();}
    inline const t_size getWindowHeight() const noexcept { return m_window->getHeight();}

    void setWindow(window_type window) { m_window = window; }
    window_type getWindow() const noexcept {  return m_window;  }

protected:

    GraphicInterface()
        :m_window()
    {}

    window_type m_window = nullptr;

    virtual void refresh() = 0;

private:
    virtual bool validId(const sdleasygui::t_id id) = 0;

};

class textDrawer
{
    SDL_Surface* textSurface;
    SDL_Texture* texture;
public:

    textDrawer(SDL_Renderer* renderer, const TFont& fontinfo, const std::string str)
        :textSurface(nullptr)
    {
        TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
        SDL_Color textColor = { fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, 0 };

        textSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    }

    inline SDL_Texture* getTexture() { return texture;}
    inline SDL_Surface* getTextSurface() { return textSurface;}

    ~textDrawer()
    {
        SDL_FreeSurface(textSurface);
    }
};


}

#endif //TETRIS_FIGURE_CLASS_TGRAPHICINTERFACE_H
