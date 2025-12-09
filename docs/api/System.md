# System API

CppEngine's System API exposes information about the underlying process and hardware.

## Source code

### Header files:

- [Arch.h](/include/cppengine/core/Arch.h)
- [Platform.h](/include/cppengine/core/Platform.h)
- [System.h](/include/cppengine/core/System.h)

### Implementation files:

- [System.cpp](/src/cppengine/core/System.cpp)

## Specification

### Public methods

| Type | Name | Description |
| --- | --- | --- |
| `static Platform` | `getPlatform()` | Returns an enum representation of the current operating system. |
| `static Arch` | `getArch()` | Returns an enum representation of the current hardware architecture type. |
| `static string` | `getCwd()` | Returns a string view of the current working directory. |