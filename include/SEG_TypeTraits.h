//
// Created by chaed on 18. 11. 25.
//

#ifndef SDLEASYGUIDE_TYPE_TRAITS_H
#define SDLEASYGUIDE_TYPE_TRAITS_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <cstdlib>
#include <random>
#include <ctime>
#include <memory>
#include <cassert>

#include "SEG_Type.h"
#include "SEG_Struct.h"

namespace sdleasygui {

template<class T>
constexpr const auto toUType(T enuml) noexcept {
    return static_cast<std::underlying_type_t<T>>(enuml);
}

template<class _Tp, class _Res, class... _Args>
inline std::shared_ptr<_Tp>
make_display(const _Res resId, _Args&&... __args)
{
    typedef typename std::remove_const<_Tp>::type _Tp_nc;
    return std::allocate_shared<_Tp>(std::allocator<_Tp_nc>(), toUType(resId),
                                     std::forward<_Args>(__args)...);
}

template<class T>
struct EnumIterator {
    T value;

    EnumIterator()
        : value(T::Begin) {}

    inline const T begin() noexcept {
        value = static_cast<T>( toUType(value) << 1);
        return value;
    }

    inline const bool end() const noexcept {
        return toUType(value) != toUType(T::End);
    }

    EnumIterator operator++() {
        value = (T) (toUType(value) << 1);
        return *this;
    }

    bool operator!=(const EnumIterator *other) {
        return toUType(value) != toUType(other->value);
    }
};

template<class T>
class EnumHelper {
public:

    static const T getRandomly() {
        const auto rnd = rand() % (toUType(T::End) - toUType(T::Begin) + 1);
        return T(rnd);
    }

    static const T getRandomly(const T begin, const T end) {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(toUType(begin), toUType(end));
        return T(distribution(generator));
    }

private:

    EnumHelper() {

    }

};

}

#endif //TERIS_FIGURE_CLASS_TTYPETRAITS_H
