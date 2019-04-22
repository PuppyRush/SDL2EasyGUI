//
// Created by chaed on 18. 12. 24.
//

#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <memory>


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>


#include "SEG_Struct.h"
#include "SEG_Constant.h"

namespace sdleasygui {

class SEG_Window final {

public:

    using unique_type = t_id;
    using window_type = SDL_Window*;
    using renderer_type = SDL_Renderer*;

    SEG_Window(const t_size width = WINDOW_WIDTH, const t_size height = WINDOW_HEIGHT);
    virtual ~SEG_Window();

    inline void setTitle(const std::string& title) { m_title = title;}
    inline void setWidth(const t_size width) noexcept { m_windowWidth = width;}
    inline void setHeight(const t_size height) noexcept { m_windowHeight = height;}
    inline const t_size getWidth() const noexcept { return m_windowWidth ;}
    inline const t_size getHeight() const noexcept { return m_windowHeight;}
    inline void setShow(const bool b) noexcept{ m_show = b; }
    void show();
    void hidden();
    void initialize();

    inline const size_t getDisplayWidth() const noexcept { return m_windowWidth; }
    inline const size_t getDisplayHeight() const noexcept { return m_windowHeight; }
    inline const t_id getWindowID() const noexcept { return m_windowID; }

    inline window_type getSDLWindow() const noexcept {
        return m_window;
    }

    inline renderer_type getSDLRenderer() const noexcept {
        return m_renderer;
    }

private:

    renderer_type m_renderer = nullptr;
    window_type m_window = nullptr;

    t_size m_windowWidth = 0;
    t_size m_windowHeight = 0;
    std::string m_title;
    t_id m_windowID = NULL_WINDOW_ID;
    bool m_show = false;
};

}

#endif //TETRIS_FIGURE_CLASS_TWINDOW_H
