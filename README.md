# CppEngine

Cross-platform game engine built in C++. This project is currently under development, and not ready for production or educational use.

## Overview

| Tool | Specification |
| --- | --- |
| C++ standard | 20 |
| CMake version | 4.2.0 |
| C++ compiler | TDM-GCC (Windows) |

## Roadmap

## Getting Started

### Setting up the TDM-GCC compiler 

1. Go to the [TDM-GCC 10.3.0 Release page](https://jmeubank.github.io/tdm-gcc/articles/2021-05/10.3.0-release). Find an appropriate installer for your device's architecture.

2. Follow the instructions on the installation wizard. When prompted, check the box labeled "Add to PATH" to register the compiler's executables to the PATH environment variable on your device.

3. Once installation is finished, click Next and restart your terminal emulator of preference.

4. To verify installation, run the following commands:

```shell
gcc --version
g++ --version
gdb --version
```

Verify that all three display a paragraph with version and/or copyright information for the executable.

# Setting up CMake on Windows

1. Go to [CMake's Downloads page](https://cmake.org/download/). Find an appropriate installer for your device's architecture.

2. Follow the instructions on the installation wizard. When prompted, check the box labeled "Add CMake to the PATH environment variable".

3. Once installation is finished, click Finish and restart your terminal emulator of preference.

4. To verify installation, run the following command:

```shell
cmake --version
```

Verify that the previous command displays a paragraph with version and/or maintainer information for the executable.

### Setting up Visual Studio Code

1. If your editor was open during the installation of TDM-GCC on your device, restart it.

2. Go to Extensions, and type "C++" in the search bar, and install the [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension by Microsoft. Optionally, install the [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) containing the aforementioned extension.

3. In the Extensions panel, now type "CMake" in the search bar, and install the [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension by Microsoft.

4. If prompted, choose to reload extensions in your Visual Studio Code window.

## Project Structure

```bash
# Project folder structure
cpp-engine/
├── include/        # C++ header files
├── src/            # C++ source code
├── CMakeLists.txt  # Project definition
├── .gitignore      # Non-commitable files
└── README.md       # <- You are here 
```

```bash
# Source folder structure
CppEngine/
├── core/           # Game engine's core modules and APIs
└── platform/       # Platform-specific code (Win32, Linux, etc.)
```

## License

