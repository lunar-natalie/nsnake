// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <random>

namespace nsnake {
    class IntGenerator {
        std::random_device m_rd;// Seed source
        std::mt19937 m_gen;     // mersenne_twister_engine

    public:
        IntGenerator() : m_gen(m_rd()) {}

        int dist(int begin, int end) {
            return std::uniform_int_distribution<>(begin, end)(m_gen);
        }
    };
}// namespace nsnake