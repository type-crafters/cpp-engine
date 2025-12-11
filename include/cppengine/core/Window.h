#pragma once
#include <limits.h>
#include <cppengine/core/Base.h>
#include <cppengine/core/WindowEvent.h>

namespace cppengine {
    using Listener = Function<void(const EventData&)>;
    
    class Window {
        protected:
            HashMap<int, Vector<Listener>> _listeners;
        public:
            // class properties
            static const int CENTER_X = INT_MIN;
            static const int CENTER_Y = INT_MAX;
            static const int SCREEN_WIDTH;
            static const int SCREEN_HEIGHT;

            // getters and setters
            virtual string getTitle() = 0;
            virtual void setTitle(string title) = 0;
            
            virtual int getX() = 0;
            virtual void setX(int x) = 0;

            virtual int getY() = 0;
            virtual void setY(int y) = 0;

            virtual int getWidth() = 0;
            virtual void setWidth(int width) = 0;

            virtual int getHeight() = 0;
            virtual void setHeight(int height) = 0;

            virtual bool isOpen() = 0;

            virtual int getClientWidth() = 0;

            virtual int getClientHeight() = 0;

            virtual void setDesktopIcon(string abspath) = 0;

            virtual void setTitleBarIcon(string abspath) = 0;

            // destructor
            virtual ~Window() = default;

            // instance methods
            template<WindowEvent E>
            void emitEvent(const typename EventDataType<E>::type& data) {
                int key = (int) E;

                auto it = _listeners.find(key);
                if (it == _listeners.end()) return;

                EventData eventVariant = data;

                for (auto& fn : it->second) {
                    fn(eventVariant);
                }
            }

            template<WindowEvent E, typename Fn>
            void addEventListener(Fn&& fn) {
                using Data = typename EventDataType<E>::type;

                Listener wrapper = [fn = std::forward<Fn>(fn)](const EventData& ev) {
                    fn(std::get<Data>(ev));
                };

                _listeners[(int)E].push_back(std::move(wrapper));
            }

            virtual void display() = 0;
            virtual void processEvents() = 0;
    };
}