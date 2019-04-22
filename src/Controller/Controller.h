//
// Created by chaed on 18. 12. 26.
//

#ifndef CONTROLLER_CONTROLL_H
#define CONTROLLER_CONTROLL_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <atomic>

#include "sdl2gfx/SDL2_gfxPrimitives.h"

#include "SDL2EasyGUI/include/SEG_Struct.h"
#include "SDL2EasyGUI/include/ControllerBuilder.h"
#include "SDL2EasyGUI/include/GroupControllManager.h"

#include "../Windows/GraphicInterface.h"

namespace sdleasygui {

class DisplayInterface;
class Controller : public GraphicInterface {

public:

    using controll_ptr = Controller*;

    virtual ~Controller() = default;

    inline const t_res getResourceId() const noexcept {
        return m_data->resourceId;
    }
    inline const TPoint &getPoint() const noexcept {
        return m_data->point;
    }
    inline void setPoint(const TPoint &point) noexcept {
        m_data->point = point;
    }
    inline const t_size getWidth() const noexcept {
        return m_data->width;
    }
    inline void setWidth(t_size width) noexcept {
        m_data->width = width;
    }
    inline const t_size getHeight() const noexcept {
        return m_data->height;
    }
    inline void setHeight(t_size height) noexcept {
        m_data->height = height;
    }
    inline const TFont &getFont() const noexcept {
        return m_data->font;
    }
    inline void setFont(const TFont &font) noexcept {
        m_data->font = font;
    }
    inline const std::string getName() const noexcept {
        return m_data->name;
    }
    inline void setName(const std::string &name) noexcept {
        m_data->name = name;
    }
    inline const bool isEnabled() const noexcept {
        return m_data->enabled;
    }
    inline void setEnabled(bool enabled) noexcept {
        m_data->enabled = enabled;
    }
    inline const ControllerKind getKind() const noexcept {
        return m_data->kind;
    }
    inline const int getGroup() const noexcept {
        return m_data->group;
    }
    inline void setGroup(int group) noexcept {
        m_data->group = group;
    }
    inline const bool isCarot() const noexcept {
        return m_data->carot;
    }
    inline void setCarot(bool carot) noexcept {
        m_data->carot = carot;
    }
    inline const t_display getDisplay() const noexcept {
        return m_data->display;
    }
    inline void setDisplay(t_display display) noexcept {
        m_data->display = display;
    }
    inline const bool getAutoSize() const noexcept {
        return m_data->autoSize;
    }
    inline const BorderBoundaryLineType getBorderBoundaryLineType() const noexcept {
        return m_data->borderLineType;
    }
    inline const BorderBoundaryType getBorderBoundaryType() const noexcept {
        return m_data->borderType;
    }
    inline const TColor &getBorderLineColor() const noexcept {
        return m_data->borderColor;
    }
    inline const int getBorderAngle() const noexcept {
        return m_data->borderAngle;
    }
    inline const int getBorderThick() const noexcept {
        return m_data->borderThick;
    }
    inline const bool isSelected() const noexcept {
        return m_data->selected;
    }

    inline const bool isFoucs() const {
        return m_isFoucs;
    }

    inline void setFoucs(bool m_isFoucs) {
        Controller::m_isFoucs = m_isFoucs;
    }

    const bool isHit(const TPoint &point);
    void setSelected(bool selected);
    void onVirtualDraw();
    void clickController(TPoint = {30,30});

    virtual void initialize();

protected:

    explicit Controller(const ControllerBuilder &bld);

    inline const bool isMultiselected() const noexcept {
        m_data->multiselected;
    }
    inline void setMultiselected(bool multiselected) noexcept {
        m_data->multiselected = multiselected;
    }

    inline std::shared_ptr<ControllerBasic> getBasic()
    {
        return m_data;
    }

    void drawBackground(const SDL_Rect rect, const TColor color);
    virtual void onDrawBackground();
    virtual void refresh();

    virtual void onCommonEvent(const SDL_CommonEvent *common) {};
    virtual void onWindowEvent(const SDL_WindowEvent &window) {};
    virtual void onKeyboardEvent(const SDL_KeyboardEvent *key);
    virtual void onTextEditingEvent(const SDL_TextEditingEvent *edit) {};
    virtual void onTextInputEvent(const SDL_TextInputEvent *text);
    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent *motion) {};
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent *button) {}
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
    virtual void onUserEvent(const SDL_UserEvent *user) {}
    virtual void onSysWMEvent(const SDL_SysWMEvent *syswm) {};
    virtual void onTouchFingerEvent(const SDL_TouchFingerEvent *tfinger) {};
    virtual void onMultiGestureEvent(const SDL_MultiGestureEvent *mgesture) {};
    virtual void onDollarGestureEvent(const SDL_DollarGestureEvent *dgesture) {};
    virtual void onDropEvent(const SDL_DropEvent *drop) {};
    virtual void onTimerEvent(const SDL_UserEvent *user) {}

    virtual void onAttachFocus() {};
    virtual void onDetachFocus() {};


    virtual void onDraw() = 0;

    int m_textWidth = 0;
    int m_textHeight = 0;
    bool m_isFoucs = false;
    std::shared_ptr<ControllerBasic> m_data;
};

}

#endif //TETRIS_FIGURE_CLASS_TCONTROLL_H
