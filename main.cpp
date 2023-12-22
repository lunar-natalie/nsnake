// Copyright (c) 2023 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#include <clocale>
#include <iostream>
#include <stdexcept>

#include "application.h"

using namespace nsnake;

int main()
try {
    // Assume ISO-8859-1 character set for curses
    setlocale(LC_ALL, "");
    // Initialize curses and start the main event loop
    Application().start();
    return 0;
} catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
}
