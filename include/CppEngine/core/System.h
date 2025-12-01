#pragma once
#include <string>
#include "Platform.h"
#include "Arch.h"

using std::string;

namespace CppEngine {
    class System {
        public:
            static Platform getPlatform();
            static Arch getArch();
    };
}