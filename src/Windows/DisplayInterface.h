
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

////////////below sources are from std::thread.
    template<std::size_t __i, typename _Tp>
    using __tuple_element_t = typename std::tuple_element<__i, _Tp>::type;

    template<typename _Tuple>
    struct _Invoker {
        _Tuple _M_t;

        template<size_t _Index>
        static __tuple_element_t<_Index, _Tuple> &&
        _S_declval();

        template<size_t... _Ind>
        auto
        _M_invoke(std::_Index_tuple<_Ind...>)
        noexcept(noexcept(std::__invoke(_S_declval<_Ind>()...)))
        -> decltype(std::__invoke(_S_declval<_Ind>()...))
        { return std::__invoke(std::get<_Ind>(std::move(_M_t))...); }

        using _Indices= typename std::_Build_index_tuple<std::tuple_size<_Tuple>::value>::__type;

        auto
        operator()()
        noexcept(noexcept(std::declval<_Invoker &>()._M_invoke(_Indices())))
        -> decltype(std::declval<_Invoker &>()._M_invoke(_Indices()))
        { return _M_invoke(_Indices()); }
    };

    template<typename... _Tp>
    using __decayed_tuple = std::tuple<typename std::decay<_Tp>::type...>;

    template<typename _Callable, typename... _Args>
    _Invoker<__decayed_tuple<_Callable, _Args...>>
    _make_invoker(_Callable &&__callable, _Args &&... __args)
    {
        return {__decayed_tuple<_Callable, _Args...>{
            std::forward<_Callable>(__callable), std::forward<_Args>(__args)...
        }};
    }
////////////////////////

    using controll_ptr = typename Controll::controll_ptr;

    virtual ~DisplayInterface();

    void addControll(const controll_ptr ctl);
    bool clickedMenuEvent(const TPoint &point);

    std::underlying_type_t<resource> modal();
    void modaless();
    void show() { getWindow()->show(); }
    void hidden() { getWindow()->hidden(); }
    t_res initialize();

    virtual void onDraw();
    virtual void refresh() override;
    virtual void postCreate() = 0;
    virtual void postDestroy() = 0;

    inline void setBackgroundImgPath(const std::string &path) { m_backgroundImgPath = path; }
    inline void setRun(const bool run) { m_run = run; }
    inline void setStopDraw(const bool set) { m_stopDraw = set; }

    inline const t_display getDisplay() const noexcept { return m_display; }
    inline const TLocalMode getMode() const noexcept { return m_mode; }
    inline const bool getRun() const noexcept { return m_run; }
    inline const bool getSetDraw() const noexcept { return m_stopDraw; }
    inline const t_id getWindowID() const noexcept { return getWindow()->getWindowID(); }
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

    template<typename _Callable, typename... _Args>
    void addLButtonClickEvent(const t_res id, _Callable &&__f, _Args &&... __args)
    {
        auto fn = _make_invoker(std::forward<_Callable>(__f),
                                std::forward<_Args>(__args)...);
        _noParamEvent(id,fn);
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

    virtual void registerEvent() {}
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
    resource m_modalresult = NONE;
};


#define SEG_EVENT_NO_PARAM(id,fx,obj) DisplayInterface::_noParamEvent(id,std::bind(fx,obj))
#define SEG_EVENT_1PARAM(id,fx,obj) DisplayInterface::_oneParamEvent(id,std::bind(fx,obj,std::placeholders::_1))
#define SEG_EVENT_2PARAM(id,fx,obj) DisplayInterface::_twoParamEvent(id,std::bind(fx,obj,std::placeholders::_1, std::placeholders::_2))

#define SEG_LBUTTONCLICK(id,fx,obj) SEG_EVENT_NO_PARAM(id,fx,obj)
#define SEG_KEYDOWN(id,fx,obj) SEG_EVENT_1PARAM(id,fx,obj)

}

#endif