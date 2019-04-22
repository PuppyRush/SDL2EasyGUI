//
// Created by chaed on 19. 3. 5.
//

#include "MessageDialog.h"

using namespace sdleasygui;

MessageDialog::MessageDialog(const std::string& message, MessageDialogKind kind)
    :DisplayInterface(toUType(MESSAGEDIALOG_MSG)), m_message(message), m_kind(kind)
{
    setWindowTitle(message);
    setWindowHeight(300);
    setWindowWidth(400);
}

void MessageDialog::registerEvent()
{
    SEG_LBUTTONCLICK(sdleasygui::toUType(resource::BTN_OK),&MessageDialog::onClickOk, this);
    SEG_LBUTTONCLICK(sdleasygui::toUType(resource::BTN_YES),&MessageDialog::onClickYes, this);
    SEG_LBUTTONCLICK(sdleasygui::toUType(resource::BTN_NO),&MessageDialog::onClickNo, this);
}

void MessageDialog::onInitialize()
{
    t_size begin_y = getWindowHeight()/2-100;
    {
        StaticLabelBuilder bld(getWindow(), {20, begin_y}, m_message);
        bld.id(sdleasygui::toUType(resource::MESSAGEDIALOG_MSG))->
            fontColor(ColorCode::black)->
            width(240)->
            height(50)->
            backgroundColor(ColorCode::white)->
            borderColor(ColorCode::yellow)->
            borderThick(3)->
            enabled(true);

        addControll(bld.build());

        auto ctl = getControll<StaticLabel>(resource::MESSAGEDIALOG_MSG);
        auto renderer = ctl->getWindow()->getSDLRenderer();
        TextDrawer textDrawer{renderer, ctl->getFont(), ctl->getString()};

        if(textDrawer.getTextWidth() > getWindowWidth())
            setWindowWidth(textDrawer.getTextWidth()+50);
    }

    //if(m_kind == MessageDialogKind::alert)
    {
        begin_y += 80;
        {
            ButtonBuilder bld(getWindow(), {getWindowWidth() - 120, begin_y+100}, "OK");
            bld.id(sdleasygui::toUType(resource::BTN_OK))->
                width(100)->
                height(50)->
                borderColor(ColorCode::white)->
                borderThick(2)->
                enabled(true);

            addControll(bld.build());
        }
    }



    DisplayInterface::onInitialize();
}

void MessageDialog::onClickOk(const void*){

    DisplayInterface::onOK();
}

void MessageDialog::onClickYes(const void*){

    DisplayInterface::onOK();
}

void MessageDialog::onClickNo(const void*){

    DisplayInterface::onNO();
}
