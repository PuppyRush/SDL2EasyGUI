
#ifndef SDLEASYGUIDE_TTYPE_H
#define SDLEASYGUIDE_TTYPE_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include <cstddef>
#include <atomic>
#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>

namespace sdleasygui {

using t_type = uint8_t;
using t_unique = uint_fast16_t;
using t_uniqueAtomic = std::atomic<t_unique>;
using t_res = unsigned int;
using t_cmd = unsigned int;
using t_display = unsigned short;

//unify typies with SDL2
using t_timer = SDL_TimerID;
using t_id = Uint32;
using t_id_atomic = std::atomic<t_id>;
using t_eventType = Uint32;


using t_coord = int;
using t_size = int;
using t_color = Uint8;
using t_time = std::time_t;
using event_type = SDL_Event *;

}

#endif