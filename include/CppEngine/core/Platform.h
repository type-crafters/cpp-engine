#pragma once
#include <string>

using std::string;

namespace CppEngine {
    enum class Platform {
        WIN_32,
        DARWIN,
        LINUX,
        UNIX,
        UNKNOWN
    };
}