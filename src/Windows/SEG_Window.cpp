//
// Created by chaed on 18. 12. 24.
//

#include <iostream>

#include "SEG_Window.h"

using namespace sdleasygui;

SEG_Window::SEG_Window(const t_size width,const t_size height)
    :m_windowHeight(height),
     m_windowWidth(width),
     m_window(nullptr),
     m_renderer(nullptr)
{

}

SEG_Window::~SEG_Window()
{
    //SDL_DestroyRenderer(m_renderer);
    //SDL_DestroyWindow(m_window);
    /*if(m_window) {
        delete m_window;
        m_window = nullptr;
    }
    if(m_renderer) {
        delete m_renderer;
        m_renderer = nullptr;
    }*/
}

void SEG_Window::initialize()
{
    using namespace std;

    try
    {

        Uint32 show = m_show ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN;
        m_window = SDL_CreateWindow(m_title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,m_windowWidth,
                                                 m_windowHeight,
                                                 show);
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        m_windowID = SDL_GetWindowID(m_window);

    }
    catch(runtime_error &e)
    {
        std::cerr << e.what();
    }
    catch(...)
    {
        std::cerr << "fail tetris game init because of unkwon error ";
    }
}


void SEG_Window::show()
{
    SDL_ShowWindow(m_window);
}

void SEG_Window::hidden()
{
    SDL_HideWindow(m_window);
}

