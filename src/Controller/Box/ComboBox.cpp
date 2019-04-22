//
// Created by chaed on 19. 3. 8.
//

#include "ComboBox.h"

using namespace sdleasygui;

ComboBox::ComboBox(BorderBuilder& bld)
    :BoxBasic(bld)
{
    bld.kind(ControllerKind::ComboBox);
}

