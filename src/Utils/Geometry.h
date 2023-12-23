// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <curses.h>

namespace nsnake {
    template<typename T>
    struct Vec2 {
        T x, y;

        template<typename U>
        constexpr Vec2<T> &operator/=(U rhs) {
            auto quotient = static_cast<Vec2<T>>(*this / rhs);
            this->x = quotient.x;
            this->y = quotient.y;
            return *this;
        }

        template<typename U>
        constexpr Vec2<T> &operator*=(U rhs) {
            auto result = static_cast<Vec2<T>>(*this * rhs);
            this->x = result.x;
            this->y = result.y;
            return *this;
        }

        explicit constexpr operator Vec2<int>() {
            return {static_cast<int>(x), static_cast<int>(y)};
        }

        static constexpr Vec2 make_uniform(T value) {
            return {value, value};
        }
    };

    using V2i = Vec2<int>;
    using V2d = Vec2<double>;
    using V2f = Vec2<float>;

    // Non-uniform arithmetic
    template<typename T>
    inline constexpr Vec2<T> operator+(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }
    template<typename T>
    inline constexpr Vec2<T> operator-(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return {lhs.x - rhs.x, lhs.y - rhs.y};
    }
    template<typename T>
    inline constexpr Vec2<T> operator*(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return {lhs.x * rhs.x, lhs.y * rhs.y};
    }
    template<typename T, typename U>
    inline constexpr V2d operator/(const Vec2<T> &lhs, const Vec2<U> &rhs) {
        return {lhs.x / static_cast<double>(rhs.x), lhs.y / static_cast<double>(rhs.y)};
    }

    // Uniform arithmetic
    template<typename T, typename U>
    inline constexpr Vec2<T> operator*(const Vec2<T> &lhs, U rhs) {
        return operator*(lhs, Vec2<T>::make_uniform(rhs));
    }
    template<typename T, typename U>
    inline constexpr V2d operator/(const Vec2<T> &lhs, U rhs) {
        return operator/(lhs, Vec2<U>::make_uniform(rhs));
    }
    template<typename T, typename U>
    inline constexpr auto operator*(T lhs, const Vec2<U> &rhs) { return operator*(rhs, lhs); }
    template<typename T, typename U>
    inline constexpr auto operator/(T lhs, const Vec2<U> &rhs) { return operator/(rhs, lhs); }
}// namespace nsnake