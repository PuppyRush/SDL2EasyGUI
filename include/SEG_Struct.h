//
// Created by chaed on 18. 12. 22.
//

#ifndef SDLEASYGUIDE_TSTRUCT_H
#define SDLEASYGUIDE_TSTRUCT_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <cassert>
#include <string>
#include <functional>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "SEG_Type.h"
#include "SEG_Property.h"

namespace sdleasygui {

typedef struct DisplayInfo {
    t_display display;
    TLocalMode mode;
    TDisplayMode displayMode;
    t_id id;

} DisplayInfo;

typedef struct TColor {
public:

    ColorCode colorCode;
    using  coldeType = decltype(colorCode) ;

    t_color r;
    t_color g;
    t_color b;
    t_color a;
    TColor() {}
    TColor(const ColorCode code, const t_color alhpa = 255)
        :colorCode(code), a(alhpa)
    {
        const auto c = std::underlying_type_t<coldeType>(code);
        r = ( c >> 16) & 0x0000FF ;
        g = ( c >> 8) & 0x0000FF;
        b = c & 0x0000FF;
    }

    TColor(const t_color r, const t_color g, const t_color b, const t_color alhpa)
        :r(r), g(g), b(b), a(alhpa)
    {

        std::underlying_type<coldeType>::type c;
        c += r << 16;
        c += g << 8;
        c += b;
        colorCode = coldeType{c};
    }

    bool operator==(const TColor &color) {
        return
            this->r == color.r
        and this->g == color.g
        and this->b == color.b;
    }

    const bool compare(const TColor &rhs) const {
        return this->colorCode == rhs.colorCode;
    }

    static SDL_Color getColor(const ColorCode colorCode) {
        TColor col(colorCode);
        SDL_Color color{col.r, col.g, col.b, 255};
        return color;
    }

    static const SDL_Color getTransparent() {
        TColor col(ColorCode::white);
        SDL_Color color{col.r, col.g, col.b, 0};
        return color;
    }
} TColor;

typedef struct TPoint {
public:
    t_coord x;
    t_coord y;
    t_coord z;

    TPoint()
        : x(0), y(0), z(0) {}

    TPoint(const t_coord x, const t_coord y, const t_coord z = 0)
        : x(x), y(y), z(z) {}

} TPoint;

typedef struct TFont {
    std::string font_name;
    t_size size;
    TColor color;
    TFont() = default;
    TFont(const std::string &str, const t_size size, const ColorCode color)
        : font_name(str), size(size), color(color) {}
} TFont;

typedef struct ControllerBasic {
    t_res resourceId;
    TPoint point = TPoint(-100, -100);
    t_size depth = 0;
    t_size width = 100;
    t_size height = 50;
    TFont font = {"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::white};
    TColor backgroundColor = ColorCode::black;
    std::string name = "";
    t_display display = std::numeric_limits<t_display>::max();
    bool enabled = true;
    bool multiselected = false;
    ControllerKind kind = ControllerKind::StaticLabel;
    int group = -1;
    bool carot = false;
    bool autoSize = true;
    bool selected = false;

    //border types
    BorderBoundaryLineType borderLineType = BorderBoundaryLineType::straight;
    BorderBoundaryType borderType = BorderBoundaryType::angle;
    TColor borderColor = ColorCode::white;
    int borderAngle = 0;
    int borderThick = 1;

    ControllerBasic() = default;
    ControllerBasic(const ControllerBasic &b)
        : resourceId(b.resourceId),
          point(b.point),
          width(b.width),
          height(b.height),
          font(b.font),
          backgroundColor(b.backgroundColor),
          name(b.name),
          display(b.display),
          enabled(b.enabled),
          multiselected(b.multiselected),
          kind(b.kind),
          group(b.group),
          carot(b.carot),
          autoSize(b.autoSize),
          selected(b.selected),
          depth(b.depth),
          borderLineType(b.borderLineType),
          borderType(b.borderType),
          borderAngle(b.borderAngle),
          borderThick(b.borderThick),
          borderColor(b.borderColor)
          { }

} TControllerBasic;

}

#endif //TETRIS_FIGURE_CLASS_TSTRUCT_H
