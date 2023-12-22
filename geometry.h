// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_GEOMETRY_H
#define NSNAKE_GEOMETRY_H

#include <curses.h>

namespace nsnake {

template<typename T>
struct Vec2 {
    T y, x;

    template<typename U>
    Vec2<T>& operator/=(U divisor)
    {
        auto quotient = static_cast<Vec2<T>>(*this / divisor);
        this->y = quotient.y;
        this->x = quotient.x;
        return *this;
    }

    explicit operator Vec2<int>()
    {
        return {.y = static_cast<int>(y), .x = static_cast<int>(x)};
    }
};

typedef Vec2<int> v2i;
typedef Vec2<double> v2d;
typedef Vec2<float> v2f;

// Non-uniform
inline v2d operator/(v2i const& dividend, v2i const& divisor)
{
    return {.y = dividend.y / static_cast<double>(divisor.y), .x = dividend.x / static_cast<double>(divisor.x)};
}

// Uniform
inline v2d operator/(v2i const& dividend, int divisor)
{
    return operator/(dividend, {.y = divisor, .x = divisor});
}

}// namespace nsnake

#endif //NSNAKE_GEOMETRY_H
