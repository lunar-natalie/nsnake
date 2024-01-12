// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

namespace nsnake {
    template<typename T>
    struct Vec2;

    using V2i = Vec2<int>;
    using V2d = Vec2<double>;
    using V2f = Vec2<float>;

    template<typename T>
    struct Vec2 {
        T x, y;

        static constexpr Vec2 uniform(T v) {
            return {v, v};
        }

        static constexpr Vec2 clamp(const Vec2 &v, const Vec2 &lo, const Vec2 &hi) {
            Vec2 ret;
            if (v.x < lo.x)
                ret.x = lo.x;
            else if (v.x > hi.x)
                ret.x = hi.x;
            else
                ret.x = v.x;

            if (v.y < lo.y)
                ret.y = lo.y;
            else if (v.y > hi.y)
                ret.y = hi.y;
            else
                ret.y = v.y;
            return ret;
        }

        template<typename U = T>
        static constexpr T product(const Vec2<U> &v) {
            return v.x * v.y;
        }

        explicit constexpr operator V2i() {
            return {static_cast<int>(x), static_cast<int>(y)};
        }

        template<typename U>
        constexpr Vec2 &operator+=(U rhs) {
            auto result = static_cast<Vec2>(*this + rhs);
            this->x = result.x;
            this->y = result.y;
            return *this;
        }
        template<typename U>
        constexpr Vec2 &operator-=(U rhs) {
            auto result = static_cast<Vec2>(*this - rhs);
            this->x = result.x;
            this->y = result.y;
            return *this;
        }
        template<typename U>
        constexpr Vec2 &operator*=(U rhs) {
            auto result = static_cast<Vec2>(*this * rhs);
            this->x = result.x;
            this->y = result.y;
            return *this;
        }
        template<typename U>
        constexpr Vec2 &operator/=(U rhs) {
            auto quotient = static_cast<Vec2>(*this / rhs);
            this->x = quotient.x;
            this->y = quotient.y;
            return *this;
        }
    };

    // Comparison
    template<typename T>
    inline constexpr bool operator==(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }
    template<typename T>
    inline constexpr bool operator!=(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return !(lhs == rhs);
    }
    template<typename T>
    inline constexpr bool operator>(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return (lhs.x > rhs.x) && (lhs.y > rhs.y);
    }
    template<typename T>
    inline constexpr bool operator<(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return (lhs.x < rhs.x) || (lhs.y < rhs.y);
    }
    template<typename T>
    inline constexpr bool operator>=(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return (lhs > rhs) || (lhs == rhs);
    }
    template<typename T>
    inline constexpr bool operator<=(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return (lhs < rhs) || (lhs == rhs);
    }

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
        return operator*(lhs, Vec2<T>::uniform(rhs));
    }
    template<typename T, typename U>
    inline constexpr V2d operator/(const Vec2<T> &lhs, U rhs) {
        return operator/(lhs, Vec2<U>::uniform(rhs));
    }
    template<typename T, typename U>
    inline constexpr auto operator*(T lhs, const Vec2<U> &rhs) {
        return operator*(rhs, lhs);
    }
    template<typename T, typename U>
    inline constexpr auto operator/(T lhs, const Vec2<U> &rhs) {
        return operator/(rhs, lhs);
    }
}// namespace nsnake
