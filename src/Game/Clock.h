// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <chrono>

namespace nsnake {
    namespace chrono = std::chrono;
    using namespace std::chrono_literals;

    static const int TARGET_FRAMERATE = 24;

    using Clock = chrono::steady_clock;
    using FrameDuration = chrono::duration<double, std::ratio<1, TARGET_FRAMERATE>>;
    using TickRate = chrono::duration<unsigned, std::milli>;
}// namespace nsnake