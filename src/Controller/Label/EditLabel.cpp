//
// Created by chaed on 18. 12. 28.
//

#include "EditLabel.h"
#include "SDL2EasyGUI/include/SEG_Event.h"
#include "SDL2EasyGUI/include/SEG_TypeTraits.h"

using namespace std;
using namespace sdleasygui;

EditLabel::EditLabel(EditLabelBuilder& bld)
    :LabelBasic(bld), m_labelBasic(bld.m_editBasic)
{
    bld.kind(ControllerKind::EditLabel);

    m_textCursorTimerAdder = make_shared<TimerAdder>(700,toUType(SEG_Event::EDITLABEL_CHAR_TEXTCURSOR));
}

void EditLabel::onDraw()
{
    if(m_textWidth>0 && m_textHeight>0) {
        const auto point = getPoint();
        SDL_Point points[]
            = {{static_cast<t_size>(point.x + m_textWidth + 7), point.y + 5},
               {static_cast<t_size>(point.x + m_textWidth + 7), point.y + static_cast<t_size>(getHeight()) - 5},
               {static_cast<t_size>(point.x + m_textWidth + 7), point.y + 5}};

        TColor lineColor;
        if (m_textCursor)
            lineColor = ColorCode::black;
        else
            lineColor = ColorCode::white;

        SDL_SetRenderDrawColor(getWindow()->getSDLRenderer(), lineColor.r, lineColor.g, lineColor.b, 255);
        SDL_RenderDrawLines(getWindow()->getSDLRenderer(), points, SDL_arraysize(points));
    }
    LabelBasic::onDraw();
}

void EditLabel::onTimerEvent(const SDL_UserEvent *user)
{
    m_textCursor = !m_textCursor;
    onDraw();
}

void EditLabel::onUserEvent (const SDL_UserEvent* user)
{
    switch(user->type)
    {
        case EDITLABEL_CHAR_TEXTCURSOR:
            m_textCursor = !m_textCursor;
            refresh();
            break;
    }
    LabelBasic::onUserEvent(user);
}

void EditLabel::onAttachFocus()
{
    if(m_textCursorTimer == NULL_TIMER_ID)
    {
        m_textCursorTimer = m_textCursorTimerAdder->addTimer();
        m_textCursor = true;
        setSelected(true);
    }
}

void EditLabel::onDetachFocus()
{
    SDL_RemoveTimer(m_textCursorTimer);
    m_textCursor = false;
    m_textCursorTimer = NULL_TIMER_ID;
    setSelected(false);
}

void EditLabel::onKeyboardEvent (const SDL_KeyboardEvent* key)
{
    if(!isSelected())
        return;

    switch(key->type)
    {
        case SDL_KEYDOWN:
            switch(key->keysym.sym)
            {
                case SDLK_BACKSPACE:
                    if(!m_labelString.empty())
                        m_labelString.pop_back();
                    break;
            }
            break;
    }

    EventPusher event{this->getWindow()->getWindowID(), this->getResourceId(), SEG_ENTER_CONTROLLER};
    event.setUserData(const_cast<SDL_KeyboardEvent*>(key));
    event.pushEvent();

    LabelBasic::onKeyboardEvent(key);
}

void EditLabel::onTextInputEvent (const SDL_TextInputEvent* text)
{
    if(!isSelected())
        return;

    m_labelString.append(text->text);
    LabelBasic::onTextInputEvent(text);
}


void EditLabel::onDrawBackground()
{
    LabelBasic::onDrawBackground();
}

void EditLabel::initialize()
{
    LabelBasic::initialize();
}

