// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef NSNAKE_APP_CONTEXT_H
#define NSNAKE_APP_CONTEXT_H

#include "utils/geometry.h"

namespace nsnake {

struct ApplicationContext {
    v2i window_extent = {0, 0};
    [[nodiscard]] v2i window_center() const { return static_cast<v2i>(window_extent / 2); }
};

}//namespace nsnake

#endif//NSNAKE_APP_CONTEXT_H
