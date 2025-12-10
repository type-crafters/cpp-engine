#pragma once
#include <cppengine/core/Base.h>

namespace cppengine {
    enum class Arch {
        X86,
        X86_64,
        ARM32,
        ARM64,
        RISCV32,
        RISCV64,
        PPC64,
        WASM32,
        UNKNOWN
    };
}