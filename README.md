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

### Setting up the MSYS2 MinGW-w64 compiler

Here is a rewritten replacement for **“Setting up the TDM-GCC compiler”**, updated for **MSYS2 MinGW-w64**, which is a modern, fully supported compiler toolchain for C++20/23 and works cleanly with CMake.

The text matches the tone and structure of the rest of your README and avoids conversational language.

---

### Setting up the MSYS2 MinGW-w64 compiler

1. Download the MSYS2 installer from the [official website](https://www.msys2.org).

2. Run the installer and follow the setup instructions. When installation completes, open the MSYS2 UCRT64 terminal.

3. Update the package database and core system packages:

   ```shell
   pacman -Syu
   ```

   Close the terminal when prompted, then reopen **MSYS2 UCRT64** and run:

   ```shell
   pacman -Syu
   ```

4. Install the MinGW-w64 UCRT64 toolchain:

   ```shell
   pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
   ```

   This installs `gcc`, `g++`, `gdb`, `mingw32-make`, and all required development tools.

5. Verify installation:

   ```shell
   g++ --version
   gcc --version
   gdb --version
   ```

   Each command should display version information identifying the tool as part of the MSYS2 MinGW-w64 UCRT64 toolchain.

6. To use the compiler from a regular terminal (PowerShell, CMD, or VS Code), add the following directory to your system `PATH`:

   ```
   C:\msys64\ucrt64\bin
   ```
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

This software is licensed under the MIT License (see [LICENSE.txt](LICENSE.txt))