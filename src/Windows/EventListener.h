//
// Created by chaed on 19. 2. 8.
//

#ifndef TETRIS_FIGURE_CLASS_EVENTLISTENER_H
#define TETRIS_FIGURE_CLASS_EVENTLISTENER_H

#include <cassert>

#include <SDL2/SDL.h>

//#include "SDLEasyGUI/SEG_Type.h"

namespace sdleasygui {

class EventListener {

public:

    virtual ~EventListener() = default;

    void onEvent(const event_type event) {
        switch (event->type) {
            case SDL_WINDOWEVENT   :
                onWindowEvent(event->window);
                switch (event->window.type) {
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        onDetachFocus();
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        onAttachFocus();
                        break;
                }
                break;
            case SDL_SYSWMEVENT    :
                onSysWMEvent(&event->syswm);
                break;
            case SDL_KEYDOWN       :
                onKeyboardEvent(&event->key);
                break;
            case SDL_KEYUP:
                break;
            case SDL_TEXTEDITING   :
                onTextEditingEvent(&event->edit);
                break;
            case SDL_TEXTINPUT:
                onTextInputEvent(&event->text);
                break;
            case SDL_KEYMAPCHANGED :
                break;
            case SDL_MOUSEMOTION   :
                onMouseMotionEvent(&event->motion);
                break;
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonEvent(&event->button);
                break;
            case SDL_MOUSEBUTTONUP :
                break;
            case SDL_MOUSEWHEEL    :
                onMouseWheelEvent(&event->wheel);
                break;
            case SDL_JOYBUTTONDOWN   :
                onJoyButtonEvent(&event->jbutton);
                break;
            case SDL_JOYBUTTONUP     :
                break;
            case SDL_JOYBALLMOTION   :
                onJoyBallEvent(&event->jball);
                break;
            case SDL_JOYHATMOTION    :
                onJoyHatEvent(&event->jhat);
                break;
            case SDL_JOYAXISMOTION   :
                onJoyAxisEvent(&event->jaxis);
                break;
            case SDL_JOYDEVICEADDED  :
            case SDL_JOYDEVICEREMOVED:
                onJoyDeviceEvent(&event->jdevice);
                break;
            case SDL_CONTROLLERAXISMOTION:
                onControllerAxisEvent(&event->caxis);
                break;
            case SDL_CONTROLLERBUTTONDOWN :
                onControllerButtonEvent(&event->cbutton);
                break;
            case SDL_CONTROLLERBUTTONUP   :
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
            case SDL_CONTROLLERDEVICEREMAPPED:
            case SDL_CONTROLLERDEVICEADDED :
                onControllerDeviceEvent(&event->cdevice);
                break;

            case SDL_FINGERDOWN:
            case SDL_FINGERUP:
            case SDL_FINGERMOTION:

            case SDL_DOLLARGESTURE:
            case SDL_DOLLARRECORD:
            case SDL_MULTIGESTURE:

            case SDL_CLIPBOARDUPDATE:

            case SDL_DROPFILE:
            case SDL_DROPBEGIN:
            case SDL_DROPCOMPLETE:
            case SDL_DROPTEXT:

            case SDL_AUDIODEVICEADDED:
            case SDL_AUDIODEVICEREMOVED:

            case SDL_RENDER_TARGETS_RESET:
            case SDL_RENDER_DEVICE_RESET :
                //not implement yet
                assert(0);
                break;
            default:
                switch (event->user.code) {
                    case ATTACH_FOCUS:
                        onAttachFocus();
                        break;
                    case DETACH_FOCUS:
                        onDetachFocus();
                        break;
                    case SDL_TIMER_EVENT:
                        onTimerEvent(&event->user);
                        break;
                    default:
                        onUserEvent(&event->user);
                }

        }
    }

    //SDL Events
    virtual void onCommonEvent(const SDL_CommonEvent *common) = 0;
    virtual void onWindowEvent(const SDL_WindowEvent &window) = 0;
    virtual void onKeyboardEvent(const SDL_KeyboardEvent *key) = 0;
    virtual void onTextEditingEvent(const SDL_TextEditingEvent *edit) = 0;
    virtual void onTextInputEvent(const SDL_TextInputEvent *text) = 0;
    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent *motion) = 0;
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent *button) = 0;
    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent *wheel) = 0;
    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent *jaxis) = 0;
    virtual void onJoyBallEvent(const SDL_JoyBallEvent *jball) = 0;
    virtual void onJoyHatEvent(const SDL_JoyHatEvent *jhat) = 0;
    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent *jbutton) = 0;
    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent *jdevice) = 0;
    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent *caxis) = 0;
    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent *cbutton) = 0;
    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent *cdevice) = 0;
    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent *adevice) = 0;
    virtual void onQuitEvent(const SDL_QuitEvent *quit) = 0;
    virtual void onUserEvent(const SDL_UserEvent *user) = 0;
    virtual void onSysWMEvent(const SDL_SysWMEvent *syswm) = 0;
    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent *tfinger) = 0;
    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent *mgesture) = 0;
    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent *dgesture) = 0;
    virtual void onDropEvent(const SDL_DropEvent *drop) = 0;
    virtual void onTimerEvent(const SDL_UserEvent *user) = 0;

    //SEG Events
    virtual void onAttachFocus() = 0;
    virtual void onDetachFocus() = 0;

protected:
    EventListener() = default;

private:

};

}

#endif //TETRIS_FIGURE_CLASS_EVENTLISTENER_H
