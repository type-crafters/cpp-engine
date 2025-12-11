#pragma once
#include <cppengine/core/Base.h> 

namespace cppengine {
    enum class Mouse : ubyte {
        NONE = 0,
        LEFT = 1 << 0,
        MIDDLE = 1 << 1,
        RIGHT = 1 << 2,
        BROWSER_BACK = 1 << 3,
        BROWSER_FORWARD = 1 << 4
    };

    inline Mouse operator|(Mouse a, Mouse b) {
        return static_cast<Mouse>(static_cast<ubyte>(a) | static_cast<ubyte>(b));
    }

    inline Mouse operator&(Mouse a, Mouse b) {
        return static_cast<Mouse>(static_cast<ubyte>(a) & static_cast<ubyte>(b));
    }
}
