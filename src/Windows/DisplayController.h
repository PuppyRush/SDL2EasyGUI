//
// Created by chaed on 18. 12. 15.
//

#ifndef GUI_GAMECONTROLLER_H
#define GUI_GAMECONTROLLER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <memory>
#include <unordered_map>
#include <queue>
#include <thread>
#include <condition_variable>

#include <boost/serialization/singleton.hpp>

#include "../SEG_Type.h"
#include "../SEG_Resource.h"
#include "DisplayInterface.h"

namespace sdleasygui {

using controll_map_key = std::pair<t_id, t_id>;
struct KeyHash {
    std::size_t operator()(const controll_map_key &obj) const {
        return std::hash<t_id>()(obj.first) * 13 + std::hash<t_id>()(obj.second) * 21;
    }
};

struct KeyEqual {
    bool operator()(const controll_map_key &lhs, const controll_map_key &rhs) const {
        return rhs.first == lhs.first &&
            rhs.second == rhs.second;
    }
};

class DisplayController : private boost::serialization::singleton<DisplayController>
{

public:
    using display_type = DisplayInterface;
    using display_ptr = std::shared_ptr<display_type> ;
    using modal_ary = std::deque<display_ptr>;
    using modaless_ary =  std::vector<display_ptr>;
    using modaless_ary_iterator = modaless_ary::const_iterator;

    friend class boost::serialization::singleton<DisplayController>;

    virtual ~DisplayController();

    void run();
    void finish();

    void modal_open(display_ptr);
    void modal_close();
    void modaless_open(display_ptr);
    void modaless_close(sdleasygui::t_id winid);
    void close(const t_id id);
    void refreshModal();

    static DisplayController& getInstance() {
        return boost::serialization::singleton<DisplayController>::get_mutable_instance();
    }

    inline bool isRunningDisplay(){return !(m_modalessAry.empty() && m_modalStack.empty());}

private:

    DisplayController();

    t_id getActivatedWindowID(const SDL_Event *event);
    display_ptr findFromId(const t_id id);

    void _release();
    void pumpEvent();

    template<class T>
    display_ptr _find(const T &ary, const t_id id);

    modaless_ary m_modalessAry;
    modal_ary m_modalStack;

    std::thread m_thread;
    std::atomic_bool m_run = true;
    std::condition_variable m_modalAryCV;
    std::mutex m_modalAryMutex;
};

struct modal_opener {

    DisplayController::display_ptr display;
    bool modal;

    explicit modal_opener(DisplayController::display_ptr display, bool m)
        :display(display), modal(m)
    {
        if(modal)
            DisplayController::getInstance().modal_open(display);
        else
            DisplayController::getInstance().modaless_open(display);

        display->postCreate(display);
    }

    ~modal_opener() {
        if(modal) {
            DisplayController::getInstance().modal_close();
        }
    }

};

}

#endif //TERIS_FIGURE_CLASS_TGAMECONTROLLER_H