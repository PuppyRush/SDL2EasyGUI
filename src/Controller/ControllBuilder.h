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

#include "../Windows/GraphicInterface.h"
#include "../SEG_Event.h"

namespace sdleasygui {

//predeclaration.
class Controll;

class ControllBuilder {
public:

    ControllBuilder(const GraphicInterface::window_type window, const TPoint &point, const std::string &str);
    ControllBuilder(const GraphicInterface::window_type window, TPoint &&point, std::string &&str);
    virtual ~ControllBuilder() = default;

    inline ControllBuilder *id(const t_id id) noexcept {
        m_basic.resourceId = id;
        return this;
    }

    inline ControllBuilder *font(const TFont &font) noexcept {
        m_basic.font = font;
        return this;
    }

    inline ControllBuilder *fontSize(const t_size &size) noexcept {
        m_basic.font.size = size;
        return this;
    }

    inline ControllBuilder *fontColor(const TColor &color) noexcept {
        m_basic.font.color = color;
        return this;
    }

    inline ControllBuilder *backgroundColor(const ColorCode color) noexcept {
        m_basic.background_color = color;
        return this;
    }

    inline ControllBuilder *width(const t_size size) noexcept {
        m_basic.autoSize = false;
        m_basic.width = size;
        return this;

    }

    inline ControllBuilder *height(const t_size size) noexcept {
        m_basic.autoSize = false;
        m_basic.height = size;
        return this;
    }

    inline ControllBuilder *enabled(const bool enable) noexcept {
        m_basic.enabled = enable;
        return this;
    }

    inline ControllBuilder *multiselected(const bool selected) noexcept {
        m_basic.multiselected = selected;
        return this;
    }

    inline ControllBuilder *grouping(const size_t idx) noexcept {
        m_basic.group = idx;
        return this;
    }

    inline ControllBuilder *carot() noexcept {
        m_basic.carot = true;
        return this;
    }

    inline ControllBuilder *selected() noexcept {
        m_basic.selected = true;
        return this;
    }

    inline ControllBuilder *borderLineType(const BorderBoundaryLineType lineType) {
        m_basic.borderLineType = lineType;
        return this;
    }
    inline ControllBuilder *borderBoundaryType(const BorderBoundaryType type) {
        m_basic.borderType = type;
        return this;
    }
    inline ControllBuilder *borderColor(const TColor &lineColor) {
        m_basic.borderColor = lineColor;
        return this;
    }
    inline ControllBuilder *borderAngle(const int borderAngle) {
        m_basic.borderAngle = borderAngle;
        return this;
    }
    inline ControllBuilder *borderThick(const int borderThick) {
        m_basic.borderThick = borderThick;
        return this;
    }

    const GraphicInterface::window_type getWindow() const {
        return m_window;
    }

    const TControllBasic &getBasic() const {
        return m_basic;
    }

    void kind(const ControllKind kind) {
        m_basic.kind = kind;
    }

    virtual Controll* build() = 0;

private:

    GraphicInterface::window_type m_window;
    TControllBasic m_basic;

};

}

#endif //TETRIS_FIGURE_CLASS_TMENUBUILDER_H
