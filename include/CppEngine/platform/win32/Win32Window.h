#pragma once
#include <string>
#include <windows.h>
#include <CppEngine/core/Window.h>


using std::string;

namespace CppEngine {
    class Win32Window : public Window {
        private:
            static const WCHAR* _WINDOW_CLASSNAME;
            void* _handle;
        public:
            Win32Window(string title, int x, int y, int width, int height);
            ~Win32Window();
            void show() override;
    };
}