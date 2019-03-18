//
// Created by chaed on 19. 2. 13.
//

#include "EventQueue.h"
#include "../SEG_Constant.h"

using namespace sdleasygui;

EventQueue::EventQueue()
    :m_isContinue(true)
{

}

EventQueue::~EventQueue()
{
    m_isContinue = false;

    std::lock_guard<std::mutex> lock(m_mutex);
    while(!m_eventQ.empty())
    {
        auto e = m_eventQ.front();
        m_eventQ.pop();
        delete e;
    }
}


void EventQueue::pushEvent(const event_type event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_eventQ.push(event);
    m_cond.notify_one();
}


const event_mover EventQueue::popEvent()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond.wait(lock, [=](){return !m_eventQ.empty() || !m_isContinue;});

    if(m_eventQ.empty() || !m_isContinue)
        return event_mover{nullptr};

    const auto msg = m_eventQ.front();
    m_eventQ.pop();
    return event_mover{msg};
}
