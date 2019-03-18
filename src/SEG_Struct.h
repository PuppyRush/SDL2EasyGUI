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
    t_color r;
    t_color g;
    t_color b;
    t_color a;
    TColor() {}
    TColor(const ColorCode code, const t_color alhpa = 255) {
        colorCode = code;
        switch (code) {
            case ColorCode::black:
                r = 0;
                g = 0;
                b = 0;
                break;
            case ColorCode::none:  //pass
            case ColorCode::white:
                r = 255;
                g = 255;
                b = 255;
                break;
            case ColorCode::red:
                r = 255;
                g = 0;
                b = 0;
                break;
            case ColorCode::green:
                r = 0;
                g = 255;
                b = 0;
                break;
            case ColorCode::blue:
                r = 0;
                g = 0;
                b = 255;
                break;
            case ColorCode::orange:
                r = 255;
                g = 140;
                b = 0;
                break;
            case ColorCode::yellow:
                r = 255;
                g = 255;
                b = 0;
                break;
            case ColorCode::purple:
                r = 127;
                g = 0;
                b = 255;
                break;
            case ColorCode::silver:
                r = 169;
                g = 169;
                b = 169;
                break;
            case ColorCode::dimgray:
                r = 99;
                g = 112;
                b = 117;
                break;
            default:
                std::cerr << "cant found : " << static_cast<int>(code) << std::endl;
                assert(0);
                break;
        }
        a = 255;
    }

    bool operator==(const TColor &color) {
        return this->r == color.r && this->g == color.g && this->b == color.b;
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

typedef struct ControllBasic {
    t_res resourceId;
    TPoint point = TPoint(-100, -100);
    t_size depth = 0;
    t_size width = 100;
    t_size height = 50;
    TFont font = {"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::white};
    TColor background_color = ColorCode::black;
    std::string name = "";
    t_display display = std::numeric_limits<t_display>::max();
    bool enabled = true;
    bool multiselected = false;
    ControllKind kind = ControllKind::StaticLabel;
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

    ControllBasic() = default;
    ControllBasic(const ControllBasic &b)
        : resourceId(b.resourceId),
          point(b.point),
          width(b.width),
          height(b.height),
          font(b.font),
          background_color(b.background_color),
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

} TControllBasic;

}

#endif //TETRIS_FIGURE_CLASS_TSTRUCT_H
