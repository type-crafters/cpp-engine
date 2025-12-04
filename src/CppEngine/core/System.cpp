#include <CppEngine/core/System.h>

namespace CppEngine {
    Platform System::getPlatform() {
        #if defined(__WIN32)
            return Platform::WIN_32;
        #elif defined(__APPLE__)
            return Platform::DARWIN;
        #elif defined(__linux__)
            return Platform::LINUX;
        #elif defined(__unix__)
            return Platform::UNIX;
        #else
            return Platform::UNKNOWN
        #endif
    }

    Arch System::getArch() {
        #if defined(__x86_64__) || defined(_M_X64)
            return Arch::X86_64;
        #elif defined(__i386__) || defined(_M_IX86)
            return Arch::X86;
        #elif defined(__aarch64__) || defined(_M_ARM64)
            return Arch::ARM64;
        #elif defined(__arm__) || defined(_M_ARM)
            return Arch::ARM32;
        #elif defined(__riscv) && __riscv_xlen == 64
            return Arch::RISCV64;
        #elif defined(__riscv) && __riscv_xlen == 32
            return Arch::RISCV32;
        #elif defined(__powerpc64__) || defined(__ppc64__)
            return Arch::PPC64;
        #elif defined(__wasm32__)
            return Arch::WASM32;
        #else
            return Arch::UNKNOWN;
        #endif
    }
}