#pragma once
#include <string>

using std::string;

namespace CppEngine {
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