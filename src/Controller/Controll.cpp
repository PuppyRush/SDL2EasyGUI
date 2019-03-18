//
// Created by chaed on 18. 12. 26.
//

#include "Controll.h"
#include "../SEG_Event.h"

using namespace sdleasygui;

Controll::Controll(const ControllBuilder& bld)
{
    m_basic = std::make_shared<ControllBasic>(bld.getBasic());
    setWindow(bld.getWindow());

}

void Controll::initialize()
{
    setSelected(m_basic->selected);

    if(m_basic->group != GroupControllManager::NONE)
    {
        GroupControllManager::getInstance()->add(m_basic->group, m_basic->resourceId);
        if(m_basic->multiselected)
            GroupControllManager::getInstance()->setMultiselect(m_basic->group);
    }
}

void Controll::onKeyboardEvent (const SDL_KeyboardEvent* key)
{
    refresh();
}

void Controll::onTextInputEvent (const SDL_TextInputEvent* text)
{
    refresh();
}

void Controll::onVirtualDraw()
{
    onDrawBackground();
    onDraw();
}


void Controll::refresh()
{
    EventPusher event{this->getWindow()->getWindowID(), this->getResourceId(), SEG_DRAW_CONTROLLER };
    event.pushEvent();
}

void Controll::setSelected(bool selected)
{
    m_basic->selected = selected;
    if(selected)
        GroupControllManager::getInstance()->select(m_basic->group, m_basic->resourceId);
}

const bool Controll::isHit(const TPoint& point)
{
    const auto& menu_point = m_basic->point;
    if (this->isEnabled() && (menu_point.x <= point.x && point.x <= menu_point.x + m_basic->width)
        && (menu_point.y <= point.y && point.y <= menu_point.y + m_basic->height)) {
        setSelected(!isSelected());

        EventPusher event{this->getWindow()->getWindowID(), this->getResourceId(), SEG_CLICKED_CONTROLLER };
        event.pushEvent();

        return true;
    }
    else {
        return false;
    }
}

bool Controll::validId(const t_id id)
{
    return getResourceId() == id;
}

void Controll::drawBackground(const SDL_Rect rect, const TColor color)
{
    auto renderer = getWindow()->getSDLRenderer();

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}
