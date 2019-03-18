//
// Created by chaed on 19. 2. 13.
//

#ifndef TETRIS_FIGURE_CLASS_EVENTDELIVERY_H
#define TETRIS_FIGURE_CLASS_EVENTDELIVERY_H

//#include "GameInterface/Type.h"
#include "../SEG_Constant.h"
#include "EventQueue.h"
#include "EventListener.h"

namespace sdleasygui {

class EventDelivery : public EventQueue {
public:

    EventDelivery() = default;
    virtual ~EventDelivery() = default;

    bool receiveEvent(const sdleasygui::t_id id, event_type event) {
        if (id == NULL_WINDOW_ID || validId(id)) {
            pushEvent(event);
            return true;
        } else
            return false;
    }

private:

    virtual bool validId(const sdleasygui::t_id id) = 0;

};

}

#endif //TETRIS_FIGURE_CLASS_EVENTDELIVERY_H
