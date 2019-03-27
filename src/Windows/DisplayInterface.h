
#ifndef GUI_DISPLAYINTERFACE_H
#define GUI_DISPLAYINTERFACE_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <future>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <atomic>
#include <thread>
#include <unordered_map>
#include <mutex>
#include <tuple>
#include <condition_variable>
#include <utility>

#include "SEG_Window.h"
#include "EventListener.h"
#include "EventQueue.h"

#include "../SEG_TypeTraits.h"
#include "../SEG_Resource.h"
#include "../SEG_Define.h"

#include "../Controller/ControllBuilder.h"
#include "../Controller/Controll.h"


namespace sdleasygui {

class DisplayInterface : public GraphicInterface{
public:

    using controll_ptr = typename Controll::controll_ptr;
    using unique_type = typename GraphicInterface::unique_type ;
    using display_ptr = std::shared_ptr<DisplayInterface>;

    virtual ~DisplayInterface();

    void addControll(const controll_ptr ctl);
    bool clickedMenuEvent(const TPoint &point);

    std::underlying_type_t<resource> modal(std::shared_ptr<DisplayInterface> display);
    void modaless(std::shared_ptr<DisplayInterface> display);
    std::underlying_type_t<resource> waitModaless();

    void show() { getWindow()->show(); }
    void hidden() { getWindow()->hidden(); }
    t_res initialize();

    virtual void onDraw();
    virtual void refresh() override;
    virtual void postCreate(display_ptr) = 0;
    virtual void postDestroy(const unique_type unique) = 0;

    inline void setBackgroundImgPath(const std::string &path) { m_backgroundImgPath = path; }
    inline void setRun(const bool run) { m_run = run; }
    inline void setStopDraw(const bool set) { m_stopDraw = set; }

    inline const t_display getDisplay() const noexcept { return m_display; }
    inline const TLocalMode getMode() const noexcept { return m_mode; }
    inline const bool isRun() const noexcept { return m_run; }
    inline const bool getSetDraw() const noexcept { return m_stopDraw; }
    inline const unique_type getWindowID() const noexcept { return getWindow()->getWindowID(); }
    inline Controll *getCurrentControll() const noexcept { return m_currentCtl; };

    template<class T>
    Controll::controll_ptr getControll(const T res) {
        return *find_if(begin(m_menus), end(m_menus), [res](Controll::controll_ptr ptr) {
          if (ptr->getResourceId() == toUType(res))
              return true;
          return false;
        });
    }

protected:
    DisplayInterface();

    inline SEG_Window::window_type getSDLWindow() const noexcept {
        return getWindow()->getSDLWindow();
    }

    inline SEG_Window::renderer_type getRenderer() const noexcept {
        return getWindow()->getSDLRenderer();
    }

    void _noParamEvent(const t_res id, const std::function<void(void)> callback_fn)
    {
        m_callback_no_param.insert(make_pair(id,callback_fn));
    }

    void _oneParamEvent(const t_res id, const std::function<void(const void*)> callback_fn)
    {
        m_callback_one_param.insert(make_pair(id,callback_fn));
    }

    void _twoParamEvent(const t_res id, const std::function<void(const void*, const void*)> callback_fn)
    {
        m_callback_two_param.insert(make_pair(id,callback_fn));
    }

    virtual void registerEvent() = 0;
    virtual void onInitialize();
    virtual void onCreate();
    virtual void onClose();
    virtual void onOK();
    virtual void onNO();
    virtual void onCancel();
    virtual void onDestroy();

    //events
    virtual void onCommonEvent(const SDL_CommonEvent *common) {};
    virtual void onWindowEvent(const SDL_WindowEvent &window) override;
    virtual void onKeyboardEvent(const SDL_KeyboardEvent *key) {};
    virtual void onTextEditingEvent(const SDL_TextEditingEvent *edit) {};
    virtual void onTextInputEvent(const SDL_TextInputEvent *text) {};
    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent *motion) ;
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent *button);
    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent *wheel) {};
    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent *jaxis) {};
    virtual void onJoyBallEvent(const SDL_JoyBallEvent *jball) {};
    virtual void onJoyHatEvent(const SDL_JoyHatEvent *jhat) {};
    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent *jbutton) {};
    virtual void onJoyDeviceEvent(const SDL_JoyDeviceEvent *jdevice) {};
    virtual void onControllerAxisEvent(const SDL_ControllerAxisEvent *caxis) {};
    virtual void onControllerButtonEvent(const SDL_ControllerButtonEvent *cbutton) {};
    virtual void onControllerDeviceEvent(const SDL_ControllerDeviceEvent *cdevice) {};
    virtual void onAudioDeviceEvent(const SDL_AudioDeviceEvent *adevice) {};
    virtual void onQuitEvent(const SDL_QuitEvent *quit) {};
    virtual void onUserEvent(const SDL_UserEvent *user);
    virtual void onSysWMEvent(const SDL_SysWMEvent *syswm) {};
    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent *tfinger) {};
    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent *mgesture) {};
    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent *dgesture) {};
    virtual void onDropEvent(const SDL_DropEvent *drop) {};
    virtual void onTimerEvent(const SDL_UserEvent *user) {}

    virtual void onAttachFocus() {};
    virtual void onDetachFocus() {};

    t_display m_display;
    TLocalMode m_mode;

    std::unordered_map<t_res, std::function<void(void)>> m_callback_no_param;
    std::unordered_map<t_res, std::function<void(const void *)>> m_callback_one_param;
    std::unordered_map<t_res, std::function<void(const void *, const void *)>> m_callback_two_param;

private:

    void _release();
    void _run(std::promise<resource> &&pm);
    void _onDrawMenus();

    std::vector<controll_ptr> m_menus;
    Controll *m_currentCtl;

    std::string m_backgroundImgPath;
    bool m_stopDraw = false;
    std::thread m_thread;
    std::atomic_bool m_run = true;
    resource m_resultResrouce = NONE;
    std::promise<resource> m_modalessPromise;
    std::future<resource> m_modalessFuture;
};


#define SEG_EVENT_NO_PARAM(id,fx,obj) DisplayInterface::_noParamEvent(id,std::bind(fx,obj))
#define SEG_EVENT_1PARAM(id,fx,obj) DisplayInterface::_oneParamEvent(id,std::bind(fx,obj,std::placeholders::_1))
#define SEG_EVENT_2PARAM(id,fx,obj) DisplayInterface::_twoParamEvent(id,std::bind(fx,obj,std::placeholders::_1, std::placeholders::_2))

#define SEG_LBUTTONCLICK(id,fx,obj) SEG_EVENT_NO_PARAM(id,fx,obj)
#define SEG_KEYDOWN(id,fx,obj) SEG_EVENT_1PARAM(id,fx,obj)

}

#endif