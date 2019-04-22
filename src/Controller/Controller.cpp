//
// Created by chaed on 18. 12. 26.
//

#include "Controller.h"

#include "SDL2EasyGUI/include/SEG_TypeTraits.h"
#include "SDL2EasyGUI/include/SEG_Event.h"

using namespace sdleasygui;

Controller::Controller(const ControllerBuilder& bld)
{
    m_data = std::make_shared<ControllerBasic>(bld.getBasic());
    setWindow(bld.getWindow());

    GraphicInterface::m_backgroundColor = m_data->backgroundColor;
}

void Controller::initialize()
{
    setSelected(m_data->selected);

    if(m_data->group != GroupControllManager::NONE)
    {
        GroupControllManager::getInstance().add(m_data->group, m_data->resourceId);
        if(m_data->multiselected)
            GroupControllManager::getInstance().setMultiselect(m_data->group);
    }
}

void Controller::onKeyboardEvent (const SDL_KeyboardEvent* key)
{

    switch(key->keysym.sym)
    {
        case SDLK_RETURN:
            if(isFoucs())
                clickController();
            break;
    }

    refresh();
}

void Controller::onTextInputEvent (const SDL_TextInputEvent* text)
{
    refresh();
}

void Controller::onDrawBackground()
{
    const auto backColor = getBackgroundColor();
    auto renderer = getWindow()->getSDLRenderer();

    SDL_Rect rect = SDL_Rect{ getPoint().x, getPoint().y, getWidth(), getHeight()};
    rect.x += getBorderThick();
    rect.y += getBorderThick();
    rect.h = (rect.h - getBorderThick()*2)+1;
    rect.w = (rect.w - getBorderThick()*2)+1;

    switch(getBorderBoundaryType())
    {
        case BorderBoundaryType::angle:
            SDL_SetRenderDrawColor(renderer, backColor.r, backColor.g, backColor.b, backColor.a);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderDrawRect(renderer, &rect);
            break;

        case BorderBoundaryType::roundedAngle:
            roundedBoxRGBA(renderer, rect.x, rect.y,  rect.x+rect.w, rect.y + rect.h, 10,
                            backColor.r, backColor.g, backColor.b, backColor.a);
            break;
        case BorderBoundaryType::ellipse:
            filledEllipseRGBA(renderer, rect.x + rect.w/2, rect.y + rect.h/2, m_textWidth /2, m_textHeight/2,
                              backColor.r, backColor.g, backColor.b, backColor.a);
            break;

        case BorderBoundaryType::round: {
            filledCircleRGBA(renderer, rect.x + rect.w/2, rect.y + rect.h/2, std::max(m_textWidth/2,m_textHeight/2),
                             backColor.r, backColor.g, backColor.b, backColor.a);

            break;
        }
    }

}

void Controller::onVirtualDraw()
{
    onDrawBackground();
    onDraw();
}


void Controller::refresh()
{
    EventPusher event{this->getWindow()->getWindowID(), this->getResourceId(), SEG_DRAW_CONTROLLER };
    event.pushEvent();
}

void Controller::setSelected(bool selected)
{
    m_data->selected = selected;
    if(selected)
        GroupControllManager::getInstance().select(m_data->group, m_data->resourceId);
}

const bool Controller::isHit(const TPoint& point)
{
    const auto& menu_point = m_data->point;
    if (this->isEnabled() && (menu_point.x <= point.x && point.x <= menu_point.x + m_data->width)
        && (menu_point.y <= point.y && point.y <= menu_point.y + m_data->height)) {
        setSelected(!isSelected());

        clickController();

        return true;
    }
    else {
        return false;
    }
}

void Controller::drawBackground(const SDL_Rect rect, const TColor color)
{
    auto renderer = getWindow()->getSDLRenderer();

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

void Controller::clickController(TPoint point)
{
    EventPusher event{this->getWindow()->getWindowID(), this->getResourceId(), SEG_CLICKED_CONTROLLER };
    event.setUserData( new SEG_Click{ point, this->getResourceId() });
    event.pushEvent();
}