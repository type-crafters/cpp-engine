#pragma once
#include <string>

using std::string;

namespace CppEngine {
    class Window {
        protected:
            Window(string title, int x, int y, int width, int height);
        public:
            virtual ~Window() = 0;
            
            static const int CENTER_X = INT_MIN;
            static const int CENTER_Y = INT_MAX;
            static const int SCREEN_WIDTH;
            static const int SCREEN_HEIGHT;

            virtual void show();
    };
}