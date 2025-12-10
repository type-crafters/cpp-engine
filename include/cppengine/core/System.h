#pragma once
#include <cppengine/core/Base.h>
#include <cppengine/core/Platform.h>
#include <cppengine/core/Arch.h>

namespace cppengine {
    class System {
        public:
            static Platform getPlatform();
            static Arch getArch();
            static path getCwd();
    };
}