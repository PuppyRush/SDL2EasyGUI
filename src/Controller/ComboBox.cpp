//
// Created by chaed on 19. 3. 8.
//

#include "ComboBox.h"

using namespace sdleasygui;

ComboBox::ComboBox(BorderBuilder& bld)
    :Border(bld)
{
    bld.kind(ControllKind::ComboBox);
}

