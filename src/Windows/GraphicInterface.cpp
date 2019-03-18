//
// Created by chaed on 19. 3. 17.
//

#include "GraphicInterface.h"

using namespace sdleasygui;

GraphicInterface::~GraphicInterface()
{
    if(m_window)
    {
        delete m_window;
        m_window = nullptr;
    }
}