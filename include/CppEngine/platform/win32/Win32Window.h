#pragma once
#include <windows.h>
#include <CppEngine/core/Window.h>

namespace CppEngine {
    class Win32Window : public Window {
        private:
            HWND _handle;
            static const string _WINDOW_CLASSNAME;
            static LRESULT CALLBACK _windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
            bool _open;
        public:
            // getters & setters
            string getTitle() override;
            void setTitle(string title) override;
            
            int getX() override;
            void setX(int x) override;

            int getY() override;
            void setY(int y) override;

            int getWidth() override;
            void setWidth(int width) override;

            int getHeight() override;
            void setHeight(int height) override;

            bool isOpen() override;

            int getClientWidth() override;

            int getClientHeight() override;

            void setDesktopIcon(string abspath) override;

            void setTitleBarIcon(string abspath) override;

            // constructor & destructor
            Win32Window(string title, int x, int y, int width, int height);
            ~Win32Window();

            // instance methods
            void display() override;
            void processEvents() override;
    };
}