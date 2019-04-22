//
// Created by chaed on 19. 3. 5.
//

#ifndef TETRIS_FIGURE_CLASS_MESSAGEDIALOG_H
#define TETRIS_FIGURE_CLASS_MESSAGEDIALOG_H

#include <string>

#include "SDL2EasyGUI/include/DisplayInterface.h"
#include "SDL2EasyGUI/src/Controller/Label/StaticLabel.h"
#include "SDL2EasyGUI/src/Controller/Button/Button.h"
#include "SDL2EasyGUI/include/SEG_Property.h"

namespace sdleasygui {

class MessageDialog : public DisplayInterface{

public:

    MessageDialog(const std::string& message, MessageDialogKind kind);
    virtual ~MessageDialog(){}

    virtual void registerEvent() override;
    virtual void onInitialize() override;

    virtual void postCreate(display_ptr display) override
    { }

    virtual void postDestroy(const unique_type unique) override
    { }

    virtual void onClose() override
    {
        DisplayInterface::onClose();
    }

    virtual bool validId(const sdleasygui::t_id id) noexcept
    {
        return getWindowID() == id;
    }

    void onClickOk(const void*);
    void onClickYes(const void*);
    void onClickNo(const void*);

private:

    std::string m_message;
    MessageDialogKind  m_kind;
};
}

#endif //TETRIS_FIGURE_CLASS_MESSAGEDIALOG_H
