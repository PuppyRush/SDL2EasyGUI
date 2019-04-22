//
// Created by chaed on 18. 12. 22.
//

#ifndef CONTROLLER_MENUBUILDER_H
#define CONTROLLER_MENUBUILDER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <set>
#include <functional>
#include <memory>
#include <atomic>

#include "SDL2EasyGUI/src/Windows/GraphicInterface.h"
#include "SEG_Event.h"

namespace sdleasygui {

//predeclaration.
class Controller;

class ControllerBuilder {
public:

    ControllerBuilder(const GraphicInterface::window_type window, const TPoint &point, const std::string &str);
    ControllerBuilder(const GraphicInterface::window_type window, TPoint &&point, std::string &&str);
    virtual ~ControllerBuilder() = default;

    inline ControllerBuilder *id(const t_id id) noexcept {
        m_basic.resourceId = id;
        return this;
    }

    inline ControllerBuilder *font(const TFont &font) noexcept {
        m_basic.font = font;
        return this;
    }

    inline ControllerBuilder *fontSize(const t_size &size) noexcept {
        m_basic.font.size = size;
        return this;
    }

    inline ControllerBuilder *fontColor(const TColor &color) noexcept {
        m_basic.font.color = color;
        return this;
    }

    inline ControllerBuilder *backgroundColor(const ColorCode color) noexcept {
        m_basic.backgroundColor = color;
        return this;
    }

    inline ControllerBuilder *width(const t_size size) noexcept {
        m_basic.autoSize = false;
        m_basic.width = size;
        return this;

    }

    inline ControllerBuilder *height(const t_size size) noexcept {
        m_basic.autoSize = false;
        m_basic.height = size;
        return this;
    }

    inline ControllerBuilder *enabled(const bool enable) noexcept {
        m_basic.enabled = enable;
        return this;
    }

    inline ControllerBuilder *multiselected(const bool selected) noexcept {
        m_basic.multiselected = selected;
        return this;
    }

    inline ControllerBuilder *grouping(const size_t idx) noexcept {
        m_basic.group = idx;
        return this;
    }

    inline ControllerBuilder *carot() noexcept {
        m_basic.carot = true;
        return this;
    }

    inline ControllerBuilder *selected() noexcept {
        m_basic.selected = true;
        return this;
    }

    inline ControllerBuilder *borderLineType(const BorderBoundaryLineType lineType) {
        m_basic.borderLineType = lineType;
        return this;
    }
    inline ControllerBuilder *borderBoundaryType(const BorderBoundaryType type) {
        m_basic.borderType = type;
        return this;
    }
    inline ControllerBuilder *borderColor(const TColor &lineColor) {
        m_basic.borderColor = lineColor;
        return this;
    }
    inline ControllerBuilder *borderAngle(const int borderAngle) {
        m_basic.borderAngle = borderAngle;
        return this;
    }
    inline ControllerBuilder *borderThick(const int borderThick) {
        m_basic.borderThick = borderThick;
        return this;
    }

    const GraphicInterface::window_type getWindow() const {
        return m_window;
    }

    const TControllerBasic &getBasic() const {
        return m_basic;
    }

    void kind(const ControllerKind kind) {
        m_basic.kind = kind;
    }

    virtual Controller* build() = 0;

private:

    GraphicInterface::window_type m_window;
    TControllerBasic m_basic;

};

}

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H
