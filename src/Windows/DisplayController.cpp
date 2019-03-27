//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>
#include <limits>

#include <SDL.h>
#include <SDL2/SDL.h>

#include "../SEG_Constant.h"
#include "../SEG_Type.h"

#include "DisplayController.h"
//#include "GameInterface/Online/PacketQueue.h"

using namespace std;
using namespace sdleasygui;

DisplayController::DisplayController()
{
}

DisplayController::~DisplayController()
{
    finish();
    /*condition_variable cv;
    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [=](){return !m_run.load();});*/
    m_thread.join();

}

void DisplayController::modal_open(display_ptr display)
{
    m_modalStack.emplace_back(display);
    m_modalAryCV.notify_one();

    display->initialize();

    if(!m_modalStack.empty())
    {
        auto parent = m_modalStack.front();
        SDL_SetWindowModalFor(display->getWindow()->getSDLWindow(),
                              parent->getWindow()->getSDLWindow());
    }

    display->refresh();

}

void DisplayController::modal_close()
{
    m_modalStack.pop_back();
}

void DisplayController::modaless_open(display_ptr display)
{
    m_modalessAry.emplace_back(display);
    m_modalAryCV.notify_one();

    display->initialize();
    display->refresh();
}

void DisplayController::modaless_close(sdleasygui::t_id winid)
{
    auto it = std::remove_if(begin(m_modalessAry), end(m_modalessAry), [winid](const auto ptr)
    {
      return winid == ptr->getWindowID();
    });
}

void DisplayController::close(const t_id id)
{
    if(!m_modalStack.empty() && m_modalStack.back()->getWindowID() == id)
    {
        auto quitDisplay = m_modalStack.back();
        m_modalStack.pop_back();
    }
    else
    {
        std::remove_if(begin(m_modalessAry), end(m_modalessAry), [id](auto display) {
          return display->getWindowID() == id;
        });
    }
}

void DisplayController::run()
{
    m_thread = std::thread(&DisplayController::pumpEvent, this);
}

void DisplayController::pumpEvent()
{
    std::unique_lock<std::mutex> lock(m_modalAryMutex);
    m_modalAryCV.wait(lock, [=](){return !m_modalStack.empty() || !m_modalessAry.empty();});

    while(m_run)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);

        const auto winid = getActivatedWindowID(&event);
        if(winid != NULL_WINDOW_ID)
        {
            if(auto display = findFromId(winid)
                ; display != nullptr)
            {
                SDL_Event* e = new SDL_Event{event};
                display->receiveEvent(winid, e);
            }
        }
        else
        {
            //broadcasting m_userEvent if not found something targeted id (display, controller)
            SDL_Event* e = new SDL_Event{event};

            if(!m_modalStack.empty())
            {
                m_modalStack.back()->receiveEvent(NULL_WINDOW_ID, e);
            }

            for(const auto modaless : m_modalessAry) {
                modaless->receiveEvent(NULL_WINDOW_ID, e);
            }
        }
    }
}


DisplayController::display_ptr DisplayController::findFromId(const t_id id)
{
    if( display_ptr display = _find(m_modalessAry, id);
        display != nullptr)
    {
        return display;
    } else{
        return _find(m_modalStack,id);
    }
}

t_id DisplayController::getActivatedWindowID(const SDL_Event* event)
{
    t_id windowId = NULL_WINDOW_ID;
    switch(event->type)
    {
        case SDL_USEREVENT:
            windowId = event->user.windowID;
            break;
        case SDL_WINDOWEVENT   :
            windowId = event->window.windowID;
            break;
        case SDL_SYSWMEVENT    :
            break;
        case SDL_KEYDOWN       :
        case SDL_KEYUP:
            windowId = event->key.windowID;
            break;
        case SDL_TEXTEDITING   :
        case SDL_TEXTINPUT:
            windowId = event->text.windowID;
            break;
        case SDL_KEYMAPCHANGED :
            break;
        case SDL_MOUSEMOTION   :
            windowId = event->motion.windowID;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP :
            windowId = event->button.windowID;
            break;
        case SDL_MOUSEWHEEL    :
            windowId = event->wheel.windowID;
            break;
        case SDL_JOYBUTTONDOWN   :
        case SDL_JOYBALLMOTION   :
        case SDL_JOYHATMOTION    :
        case SDL_JOYAXISMOTION   :
        case SDL_JOYBUTTONUP     :
        case SDL_JOYDEVICEADDED  :
        case SDL_JOYDEVICEREMOVED:
            break;
    }
    return windowId;
}


template <class T>
DisplayController::display_ptr DisplayController::_find(const T& ary, const t_id id)
{
    auto it = std::find_if(begin(ary), end(ary), [id](const auto ptr)
    {
      return id == ptr->getWindowID();
    });
    return it == ary.end() ? nullptr : *it;
}


void DisplayController::_release()
{
}

void DisplayController::finish()
{
    for(const auto display : m_modalStack)
    {
        EventPusher event{display->getWindowID(), WINDOW_CLOSE };
        event.pushEvent();
    }

    for(const auto display : m_modalessAry)
    {
        EventPusher event{display->getWindowID(), WINDOW_CLOSE };
        event.pushEvent();
    }

   /* while(!m_modalStack.empty())
    {
        if(!(*m_modalStack.begin())->isRun())
        {
            delete m_modalStack.front();
            m_modalStack.pop_front();
        }
    }

    while(!m_modalessAry.empty())
    {
        if(!(*m_modalessAry.begin())->isRun())
        {
            auto dis = *m_modalessAry.begin();
            m_modalessAry.erase(m_modalessAry.begin());
            delete dis;
        }
    }*/

    m_run.exchange(false);
}

void DisplayController::refreshModal()
{
    for(const auto display : m_modalStack)
        display->onDraw();
    for(const auto display : m_modalessAry)
        display->onDraw();
}