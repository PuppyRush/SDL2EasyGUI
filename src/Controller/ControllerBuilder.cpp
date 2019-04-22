//
// Created by chaed on 18. 12. 22.
//

#include "include/ControllerBuilder.h"
#include "SDL2EasyGUI/include/GroupControllManager.h"

using namespace sdleasygui;

ControllerBuilder::ControllerBuilder(const GraphicInterface::window_type window,const TPoint& point, const std::string& str)
    :m_window(window)
{
    m_basic.point = point;
    m_basic.name = str;
}

ControllerBuilder::ControllerBuilder(const GraphicInterface::window_type window, TPoint&& point, std::string&& str)
    :m_window(window)
{
    m_basic.point = point;
    m_basic.name = str;
}
