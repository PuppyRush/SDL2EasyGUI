//
// Created by chaed on 19. 2. 13.
//

#ifndef TETRIS_FIGURE_CLASS_EVENTQUEUE_H
#define TETRIS_FIGURE_CLASS_EVENTQUEUE_H

#include <queue>
#include <condition_variable>
#include <atomic>

#include <SDL2/SDL.h>

#include "../SEG_Type.h"

namespace sdleasygui {

struct event_mover {
    const event_type event = nullptr;
    explicit event_mover(const event_type event)
        : event(event) {};

    ~event_mover() {
        if(event->type >= 0x8000)
        {
            /*if(event->user.data1 != nullptr)
                delete event->user.data1;
            if(event->user.data2 != nullptr)
                delete event->user.data2;*/
        }
        //if (event)
        //    delete event;
    }
};

class EventQueue {

public:

    EventQueue();
    virtual ~EventQueue();

    void pushEvent(const event_type event);
    const event_mover popEvent();

private:
    std::queue<event_type> m_eventQ;
    std::condition_variable m_cond;
    std::mutex m_mutex;
    std::atomic_bool m_isContinue;

};

}

#endif //TETRIS_FIGURE_CLASS_EVENTQUEUE_H
