//
// Created by chaed on 18. 12. 26.
//

#ifndef CONTROLLER_CONTROLL_H
#define CONTROLLER_CONTROLL_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <atomic>

#include "../SEG_Struct.h"
#include "../Windows/GraphicInterface.h"
#include "ControllBuilder.h"
#include "GroupControllManager.h"

namespace sdleasygui {

class Controll : public GraphicInterface {

public:

    using controll_ptr = Controll*;

    virtual ~Controll() = default;

    inline const t_res getResourceId() const noexcept {
        return m_basic->resourceId;
    }
    inline const TPoint &getPoint() const noexcept {
        return m_basic->point;
    }
    inline void setPoint(const TPoint &point) noexcept {
        m_basic->point = point;
    }
    inline const t_size getWidth() const noexcept {
        return m_basic->width;
    }
    inline void setWidth(t_size width) noexcept {
        m_basic->width = width;
    }
    inline const t_size getHeight() const noexcept {
        return m_basic->height;
    }
    inline void setHeight(t_size height) noexcept {
        m_basic->height = height;
    }
    inline const TFont &getFont() const noexcept {
        return m_basic->font;
    }
    inline void setFont(const TFont &font) noexcept {
        m_basic->font = font;
    }
    inline const TColor getBackgroundColor() const noexcept {
        return m_basic->background_color;
    }
    inline void setBackground_color(const TColor &background_color) noexcept {
        m_basic->background_color = background_color;
    }
    inline const std::string getName() const noexcept {
        return m_basic->name;
    }
    inline void setName(const std::string &name) noexcept {
        m_basic->name = name;
    }
    inline const bool isEnabled() const noexcept {
        return m_basic->enabled;
    }
    inline void setEnabled(bool enabled) noexcept {
        m_basic->enabled = enabled;
    }
    inline const ControllKind getKind() const noexcept {
        return m_basic->kind;
    }
    inline const int getGroup() const noexcept {
        return m_basic->group;
    }
    inline void setGroup(int group) noexcept {
        m_basic->group = group;
    }
    inline const bool isCarot() const noexcept {
        return m_basic->carot;
    }
    inline void setCarot(bool carot) noexcept {
        m_basic->carot = carot;
    }
    inline const t_display getDisplay() const noexcept {
        return m_basic->display;
    }
    inline void setDisplay(t_display display) noexcept {
        m_basic->display = display;
    }
    inline const bool getAutoSize() const noexcept {
        return m_basic->autoSize;
    }
    inline const BorderBoundaryLineType getBorderBoundaryLineType() const noexcept {
        return m_basic->borderLineType;
    }
    inline const BorderBoundaryType getBorderBoundaryType() const noexcept {
        return m_basic->borderType;
    }
    inline const TColor &getBorderLineColor() const noexcept {
        return m_basic->borderColor;
    }
    inline const int getBorderAngle() const noexcept {
        return m_basic->borderAngle;
    }
    inline const int getBorderThick() const noexcept {
        return m_basic->borderThick;
    }
    inline const bool isSelected() const noexcept {
        return m_basic->selected;
    }

    inline const bool isFoucs() const {
        return m_isFoucs;
    }

    inline void setFoucs(bool m_isFoucs) {
        Controll::m_isFoucs = m_isFoucs;
    }

    void setSelected(bool selected);
    const bool isHit(const TPoint &point);
    void onVirtualDraw();

    virtual void initialize();

protected:

    explicit Controll(const ControllBuilder &bld);

    inline const bool isMultiselected() const noexcept {
        m_basic->multiselected;
    }
    inline void setMultiselected(bool multiselected) noexcept {
        m_basic->multiselected = multiselected;
    }

    void drawBackground(const SDL_Rect rect, const TColor color);
    virtual void onDraw() = 0;
    virtual void onDrawBackground() = 0;
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

    bool m_isFoucs = false;
    std::shared_ptr<ControllBasic> m_basic;

private:
    virtual bool validId(const sdleasygui::t_id id) override final;
};

}

#endif //TETRIS_FIGURE_CLASS_TCONTROLL_H
