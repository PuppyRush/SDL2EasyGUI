//
// Created by chaed on 18. 11. 24.
//

#ifndef SDLEASYGUIDE_TPROPERTY_H
#define SDLEASYGUIDE_TPROPERTY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

namespace sdleasygui {

const t_size WINDOW_HEIGHT = 900;
const t_size WINDOW_WIDTH = 1000;

enum class ControllerKind : t_type {
    ListBox,
    StaticLabel,
    EditLabel,
    Button,
    RadioButton,
    Border,
    ComboBox
};

enum class TDisplayMode : t_type {
    Modal,
    Modaless
};

enum class TLocalMode : t_type {
    Local,
    Online,
    All
};

enum class ColorCode : Uint32 {

    //basic color
    red = 0xFF0000,
    blue = 0x0000FF,
    orange = 0xFFA500,
    yellow = 0xFFFF00,
    purple = 0x800080,
    green = 0x008000,
    black = 0x000000,
    white = 0xFFFFFF,
    lime = 0x00FF00,
    cyan = 0x00FFFF,
    olive = 0x808000,
    navy = 0x000080,

    //gray
    silver = 0xC0C0C0,
    gray = 0x808080,
    darkgray = 0xA9A9A9,
    lightgray = 0xD3D3D3,
    dimgray = 0x696969,

    none = white,
    Begin = red,
    End = green
};

enum EventType {
    SEG_EASYGUI_EVENT_START = 0x9001,
    SEG_DRAW_DISPLAY,
    SEG_DRAW_CONTROLLER,
    SEG_CLICKED_CONTROLLER,
    SEG_ENTER_CONTROLLER
};

enum class BorderBoundaryType : t_type {
    angle,
    ellipse,
    roundedAngle,
    round
};

enum class BorderBoundaryLineType : t_type {
    none,
    straight,
    single_dashed,
    double_dashed,
    round,
    rectagle,
};

enum SEG_Event {

    SEGEVENT_START = 0x8500,
    ADD_MODAL_DISPLAY,
    ADD_MODALESS_DISPLAY,
    REFRESH_DISPLAY,
    WINDOW_CLOSE,
    SDL_TIMER_EVENT,
    DETACH_FOCUS,
    ATTACH_FOCUS,
    EDITLABEL_CHAR_TEXTCURSOR

};

enum class MessageDialogKind
{
    error,
    warining,
    alert
};

}

#endif //TERIS_FIGURE_CLASS_TPROPERTY_H
