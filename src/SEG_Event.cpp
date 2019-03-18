//
// Created by chaed on 19. 2. 17.
//

#include "SEG_Event.h"
#include "SEG_Property.h"

namespace sdleasygui {

Uint32 timerCallback(Uint32 interval, void *param) {

    SDL_UserEvent *myevent = reinterpret_cast<SDL_UserEvent *>(param);

/*
    SDL_TimerEvent timerevent;
    timerevent.data1 = myevent->data1;
    timerevent.data2 = myevent->data2;
*/

    SDL_UserEvent userevent;
    userevent.type = myevent->type;
    userevent.code = SDL_TIMER_EVENT;
    userevent.data1 = myevent->data1;
    userevent.data2 = myevent->data2;

    SDL_Event event;
    event.type = myevent->type;
    event.user = userevent;

    SDL_PushEvent(&event);
    return (interval);
}

}