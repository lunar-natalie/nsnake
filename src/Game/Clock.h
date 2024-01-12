// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <chrono>

namespace nsnake {
    static const int TARGET_FRAMERATE = 24;

    namespace chrono = std::chrono;
    using namespace std::chrono_literals;
    using Clock = chrono::steady_clock;

    using FrameDuration = chrono::duration<double, std::ratio<1, TARGET_FRAMERATE>>;
}// namespace nsnake