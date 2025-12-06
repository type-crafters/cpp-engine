#pragma once
#include <CppEngine/core/Base.h>
#include <CppEngine/core/Platform.h>
#include <CppEngine/core/Arch.h>

namespace CppEngine {
    class System {
        public:
            static Platform getPlatform();
            static Arch getArch();
            static string getCwd();
    };
}