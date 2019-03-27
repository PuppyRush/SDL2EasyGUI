//
// Created by chaed on 18. 12. 16.
//
#include <iostream>
#include <exception>
#include <algorithm>

#include "DisplayController.h"
#include "DisplayInterface.h"
#include "../SEG_Resource.h"

using namespace std;
using namespace sdleasygui;

DisplayInterface::DisplayInterface()
    :m_currentCtl(nullptr)
{
    m_window = new SEG_Window;
}


DisplayInterface::~DisplayInterface()
{
    onClose();
}

void DisplayInterface::onInitialize()
{
    registerEvent();
}

t_res DisplayInterface::initialize()
{
    getWindow()->initialize();

    onCreate();
    onInitialize();
    show();

}

std::underlying_type_t<resource> DisplayInterface::modal(std::shared_ptr<DisplayInterface> display)
{
    modal_opener opener{display, true};

    promise<resource> pm;
    auto f = pm.get_future();

    m_thread = thread(&DisplayInterface::_run, this, std::move(pm) );
    m_thread.join();

    return toUType(f.get());
}

void DisplayInterface::modaless(std::shared_ptr<DisplayInterface> display)
{
    modal_opener opener{display, false};

    m_modalessFuture = m_modalessPromise.get_future();
    m_thread = thread(&DisplayInterface::_run, this, std::move(m_modalessPromise));
}

std::underlying_type_t<resource> DisplayInterface::waitModaless()
{
    m_thread.join();
    return toUType(m_modalessFuture.get());
}

void DisplayInterface::_run(std::promise<resource> &&pm){

    while(m_run)
    {
        const event_mover e = popEvent();
        onEvent(e.event);

        if( m_currentCtl )
        {
            m_currentCtl->onEvent(e.event);
        }
    }

    pm.set_value(m_resultResrouce);
}

void DisplayInterface::onUserEvent(const SDL_UserEvent* event) {
    switch (event->code) {
        case SEG_CLICKED_CONTROLLER:
        {
            t_res id = *static_cast<t_res*>(event->data1);
            if(m_callback_no_param.count(id)>0)
                m_callback_no_param.at(id)();
            break;
        }
        case SEG_ENTER_CONTROLLER:
        {
            t_res id = *static_cast<t_res*>(event->data1);
            SDL_KeyboardEvent* keyevent = static_cast<SDL_KeyboardEvent*>(event->data2);
            if(m_callback_one_param.count(id)>0)
                m_callback_one_param.at(id)(keyevent);
            break;
        }
        case SEG_DRAW_DISPLAY:
            //dont call _refresh() in this case.
            onDraw();
            break;
        case SEG_DRAW_CONTROLLER:
        {
            refresh();
            break;
        }
        case WINDOW_CLOSE:
            onClose();
            break;
        default:;
    }
}

void DisplayInterface::onMouseButtonEvent (const SDL_MouseButtonEvent* button)
{
    clickedMenuEvent(TPoint{button->x, button->y});
    refresh();
}

void DisplayInterface::onMouseMotionEvent(const SDL_MouseMotionEvent *motion)
{
}


void DisplayInterface::onWindowEvent (const SDL_WindowEvent& window)
{
    switch(window.event)
    {
        case SDL_WINDOWEVENT_MAXIMIZED:
        case SDL_WINDOWEVENT_MOVED:
        case SDL_WINDOWEVENT_SHOWN:
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_RESTORED:
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            refresh();
            break;
        case SDL_WINDOWEVENT_CLOSE:
            onDestroy();
            break;
    }
    DisplayController::getInstance().refreshModal();
}

void DisplayInterface::onCreate()
{
    refresh();
}

void DisplayInterface::_release()
{
    auto renderer = getRenderer();

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void DisplayInterface::onClose()
{
    if(m_resultResrouce == resource::NONE)
        m_resultResrouce = resource::BTN_CLOSE;

    setRun(false);
    hidden();
    onDestroy();

}

void DisplayInterface::onOK()
{
    m_resultResrouce = BTN_OK;
    onClose();
}

void DisplayInterface::onNO(){
    m_resultResrouce = BTN_NO;
    onClose();
}

void DisplayInterface::onCancel()
{
    m_resultResrouce = BTN_CANCEL;
    onClose();
}

void DisplayInterface::onDestroy()
{

}

void DisplayInterface::onDraw()
{
    _onDrawMenus();
    _release();
}

void DisplayInterface::_onDrawMenus()
{
    for(const auto& menu : m_menus)
    {
        menu->onVirtualDraw();
    }
}

void DisplayInterface::addControll(const controll_ptr ctl)
{
    ctl->initialize();
    m_menus.emplace_back(ctl);
}

bool DisplayInterface::clickedMenuEvent(const TPoint& point)
{
    for(const auto& menu : m_menus)
    {
        if(menu->isHit(point))
        {
            m_currentCtl = menu;

            EventPusher event{this->getWindowID(), menu->getResourceId(), ATTACH_FOCUS };
            event.pushEvent();
            return true;
        }
        else
        {
            EventPusher event{this->getWindowID(), menu->getResourceId(), DETACH_FOCUS };
            event.pushEvent();
        }
    }
    return false;
}

void DisplayInterface::refresh()
{
    EventPusher event{this->getWindowID(), SEG_DRAW_DISPLAY };
    event.pushEvent();
}

