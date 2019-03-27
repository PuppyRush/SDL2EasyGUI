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

enum class ControllKind : t_type {
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

enum class ColorCode : t_type {
    red = 0,
    blue,
    orange,
    yellow,
    purple,
    green,
    black,
    white,
    silver,
    dimgray,
    none,
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

}

#endif //TERIS_FIGURE_CLASS_TPROPERTY_H
