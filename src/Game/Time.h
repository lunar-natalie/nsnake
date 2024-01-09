// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <chrono>

namespace nsnake {
    namespace chrono = std::chrono;
    using namespace std::chrono_literals;

    using Clock = chrono::steady_clock;

    constexpr static int TARGET_FRAMERATE = 24;

    using FrameDuration = chrono::duration<double, std::ratio<1, TARGET_FRAMERATE>>;
    constexpr static auto ONE_FRAME = FrameDuration(0.5s);
}// namespace nsnake