#pragma once
#include <string>
#include <CppEngine/core/Platform.h>
#include <CppEngine/core/Arch.h>


using std::string;

namespace CppEngine {
    class System {
        public:
            static Platform getPlatform();
            static Arch getArch();
    };
}