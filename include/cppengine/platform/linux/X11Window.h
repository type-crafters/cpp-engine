#pragma once
#include <X11/Xlib.h> 
#include <cppengine/core/Window.h>

namespace cppengine {
    using XWindow = ::Window;
    class X11Window : public Window {
        private:
            Display* _display;
            XWindow _window;
            bool _open;
            Atom _wmDelete;
            int _currentX;
            int _currentY;
            int _currentWidth;
            int _currentHeight;
            bool _getFrameExtents(long& left, long& right, long& top, long& botom);
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
            X11Window(string title, int x, int y, int width, int height);
            ~X11Window();

            // instance methods
            void display() override;
            void processEvents() override;
    };
}