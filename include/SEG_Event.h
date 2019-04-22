//
// Created by chaed on 19. 2. 6.
//

#ifndef TETRIS_FIGURE_CLASS_EVENT_H
#define TETRIS_FIGURE_CLASS_EVENT_H

#include <cassert>
#include <type_traits>

#include <SDL2/SDL.h>

#include "SEG_Type.h"
#include "SEG_Struct.h"
#include "SEG_TypeTraits.h"
#include "SEG_Resource.h"

namespace sdleasygui {

typedef struct SEG_Click
{
    TPoint point = {-100,-100};
    t_res resourceId = toUType(resource::NONE);

    SEG_Click(const TPoint& point, const t_res& res)
    :point(point), resourceId(res)
    {}

    SEG_Click(TPoint&& point, t_res&& res)
        :point(point), resourceId(res)
    {}
}SEG_Click;


constexpr const int timer_code = 123456789;

typedef struct SDL_TimerEvent
{
    Uint32 timer_id;
    Uint32 timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    Uint32 windowID;    /**< The associated window if any */
    Sint32 code;        /**< User defined event code */
    void *data1;        /**< User defined data pointer */
    void *data2;        /**< User defined data pointer */
} SDL_TimerEvent;



//must call by TimerAdder
Uint32 timerCallback(Uint32 interval, void *param);

class TimerAdder final {
public:

    TimerAdder(const Uint32 interval, const t_eventType event)
        : m_interval(interval), m_eventType(event) {
        m_userEvent.type = event;
    }

    inline TimerAdder *windowsId(const t_id id) {
        this->m_userEvent.windowID = id;
        return this;
    }

    inline TimerAdder *timestamp(const Uint32 time) {
        this->m_userEvent.timestamp = time;
        return this;
    }

    inline TimerAdder *data1(void *data) {
        this->m_userEvent.data1 = data;
        return this;
    }

    inline TimerAdder *data2(void *data) {
        this->m_userEvent.data2 = data;
        return this;
    }

    const t_timer addTimer() {
        m_userEvent.timestamp = SDL_GetTicks();
        return SDL_AddTimer(m_interval, timerCallback, &m_userEvent);
    }

private:

    const t_eventType m_eventType;
    const Uint32 m_interval;
    SDL_UserEvent m_userEvent;
};


template <class _Target1, class _Target2 = t_res>
class EventPusher
{
public:


    EventPusher(const _Target1 winid, const t_eventType event)
    :EventPusher()
    {
        m_user.type = SDL_USEREVENT;
        m_user.windowID = winid;
        m_user.code = event;
        m_event.type = SDL_USEREVENT;
    }

    EventPusher(const _Target1 winid, const _Target2 targetid, const t_eventType event)
        :EventPusher()
    {
        m_user.type = SDL_USEREVENT;
        m_user.windowID = winid;
        m_user.code = event;
        m_user.data1 = static_cast<void*>(new _Target2(targetid));
        m_event.type = SDL_USEREVENT;
    }

    ~EventPusher()
    {
    }

    template <class T>
    void setUserData(T* data)
    {
        auto newdata = new T{*data};
        m_user.data2 = newdata;
    }

    void pushEvent()
    {
        m_user.timestamp = SDL_GetTicks();
        m_event.user = m_user;
        SDL_PushEvent(&m_event);
    }

private:

    EventPusher()
    {
        m_user.data1 = nullptr;
        m_user.data2 = nullptr;
    }

    SDL_Event m_event;
    SDL_UserEvent m_user;
};

}

#endif //TETRIS_FIGURE_CLASS_EVENT_H
