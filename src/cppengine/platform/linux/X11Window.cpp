#include <stdexcept> 
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cppengine/platform/linux/X11Window.h>

namespace cppengine {
    const int Window::SCREEN_HEIGHT = 0;
    const int Window::SCREEN_WIDTH = 0; 

    bool X11Window::_getFrameExtents(long& left, long& right, long& top, long& bottom) {
        Atom atom = XInternAtom(_display, "_NET_FRAME_EXTENTS", True);
        if (!atom) return false;

        Atom type;
        int format;
        unsigned long n, bytes;
        unsigned char* data = nullptr;

        if (XGetWindowProperty(
                _display,
                _window,
                atom,
                0, 4,
                False,
                XA_CARDINAL,
                &type,
                &format,
                &n,
                &bytes,
                &data
            ) != Success || !data)
            return false;

        long* ext = reinterpret_cast<long*>(data);
        left   = ext[0];
        right  = ext[1];
        top    = ext[2];
        bottom = ext[3];

        XFree(data);
        return true;
    }

    string X11Window::getTitle() {
        Atom netWmName = XInternAtom(_display, "_NET_WM_NAME", True);
        Atom utf8 = XInternAtom(_display, "UTF8_STRING", True);

        Atom type;
        int format;
        unsigned long nItems;
        unsigned long bytes;
        unsigned char* prop = nullptr;

        if (XGetWindowProperty(
            _display,
            _window,
            netWmName,
            0,
            (~0L),
            False,
            utf8,
            &type,
            &format,
            &nItems,
            &bytes,
            &prop
        ) == Success && prop) {
            string title(reinterpret_cast<char*>(prop), nItems);
            XFree(prop);
            return title;
        }

        XTextProperty textProp;
        if (XGetWMName(_display, _window, &textProp) && textProp.value) {
            string title(reinterpret_cast<char*>(textProp.value));
            return title;
        }

        return "";
    }

    void X11Window::setTitle(string title) {
        XTextProperty prop;
        char* cString = const_cast<char*>(title.c_str());
        Xutf8TextListToTextProperty(_display, &cString, 1, XUTF8StringStyle, &prop);

        XSetWMName(_display, _window, &prop);
        XSetWMIconName(_display, _window, &prop);

        XFree(prop.value);

        Atom netWmName = XInternAtom(_display, "_NET_WM_NAME", False);
        Atom utf8String = XInternAtom(_display, "UTF8_STRING", False);

        XChangeProperty(
            _display,
            _window,
            netWmName,
            utf8String,
            8,
            PropModeReplace,
            reinterpret_cast<const unsigned char*>(title.c_str()),
            title.size()
        );

        XFlush(_display);
    }
    
    int X11Window::getX() {
        int clientX, clientY;
        XWindow w;

        XTranslateCoordinates(
            _display,
            _window,
            DefaultRootWindow(_display),
            0, 0,
            &clientX,
            &clientY,
            &w
        );

        long left, right, top, bottom;
        if (_getFrameExtents(left, right, top, bottom)) {
            return clientX - left;
        }
        return clientX;
    }

    void X11Window::setX(int x) {
        long left, right, top, bottom;
        if (!_getFrameExtents(left, right, top, bottom)) {
            XMoveWindow(_display, _window, x, getY());
            return;
        }

        // clientX = newFrameX + left
        int newClientX = x + left;

        int clientX, clientY;
        XWindow w;
        XTranslateCoordinates(
            _display, _window,
            DefaultRootWindow(_display),
            0, 0,
            &clientX, &clientY,
            &w
        );

        XMoveWindow(_display, _window, newClientX, clientY);
    }


    int X11Window::getY() {
        int clientX, clientY;
        XWindow w;

        XTranslateCoordinates(
            _display,
            _window,
            DefaultRootWindow(_display),
            0, 0,
            &clientX,
            &clientY,
            &w
        );

        long left, right, top, bottom;
        if (_getFrameExtents(left, right, top, bottom)) {
            return clientY - top;
        }

        return clientY;
    }

    void X11Window::setY(int y) {
        long left, right, top, bottom;
        if (!_getFrameExtents(left, right, top, bottom)) {
            XMoveWindow(_display, _window, getX(), y);
            return;
        }

        int newClientY = y + top;

        int clientX, clientY;
        XWindow w;
        XTranslateCoordinates(
            _display, _window,
            DefaultRootWindow(_display),
            0, 0,
            &clientX, &clientY,
            &w
        );

        XMoveWindow(_display, _window, clientX, newClientY);
    }

    int X11Window::getWidth() { }

    void X11Window::setWidth(int width) { }

    int X11Window::getHeight() { }

    void X11Window::setHeight(int height) { }

    int X11Window::getClientWidth() { }

    int X11Window::getClientHeight() { }

    bool X11Window::isOpen() {
        return _open;
    }

    void X11Window::setDesktopIcon(string abspath) { }

    void X11Window::setTitleBarIcon(string abspath) { }

    void X11Window::display() {
        if (!_display || !_window) {
            throw std::runtime_error("Window creation failed.");
        }
        XMapWindow(_display, _window);
        XFlush(_display);
    }

    void X11Window::processEvents() {
        XEvent event;
        XNextEvent(_display, &event);

        switch (event.type) {
            case ClientMessage:
                if (event.xclient.data.l[0] == _wmDelete) {
                    emitEvent<WindowEvent::CLOSE>({});
                }
            case ConfigureNotify:
                XConfigureEvent* config = &event.xconfigure;
                if (_currentX != config -> x || _currentY != config -> y) {
                    emitEvent<WindowEvent::MOVE>({
                        config -> x,
                        config -> y
                    });
                    _currentX = config -> x;
                    _currentY = config -> y;
                }
                if (_currentWidth != config -> width || _currentHeight != config -> height) {
                    emitEvent<WindowEvent::RESIZE>({
                        config -> width,
                        config -> height
                    });
                    _currentWidth = config -> width;
                    _currentHeight = config -> height;
                }
            case FocusIn:
                emitEvent<WindowEvent::FOCUS>({}); 
            case FocusOut:
                emitEvent<WindowEvent::BLUR>({});
            case KeyPress:
                emitEvent<WindowEvent::KEYDOWN>({ Keyboard::UNKNOWN });  // @todo create real mapping
            case KeyRelease:
                emitEvent<WindowEvent::KEYUP>({ Keyboard::UNKNOWN });  // @todo create real mapping
            case ButtonPress:
                XButtonEvent* btn = &event.xbutton;

                emitEvent<WindowEvent::MOUSEDOWN>({
                    Mouse::NONE, 
                    Mouse::NONE, 
                    btn -> x, 
                    btn -> y
                }); // @todo create real mapping
            case ButtonRelease:
                XButtonEvent* btn = &event.xbutton;
                emitEvent<WindowEvent::MOUSEUP>({
                    Mouse::NONE, 
                    Mouse::NONE, 
                    btn -> x, 
                    btn -> y
                }); // @todo create real mapping
            case MotionNotify:
                XMotionEvent* m = &event.xmotion;
                emitEvent<WindowEvent::MOUSEMOVE>({
                    Mouse::NONE,
                    Mouse::NONE,
                    m -> x,
                    m -> y
                }); // @todo create real mapping
        }
    }

    X11Window::X11Window(string title, int x, int y, int width, int height) {
        using XWindow = ::Window;
        _display = XOpenDisplay(nullptr);
        if (!_display) {
            throw std::runtime_error("Connection to the X11 server failed.");
        }

        int screen = DefaultScreen(_display);
        XWindow root = RootWindow(_display, screen);

        if (x == CENTER_X) {
            x = (SCREEN_WIDTH - width) / 2;
        }

        if (y == CENTER_Y) {
            y = (SCREEN_HEIGHT - height) / 2;
        }
        
        _window = XCreateSimpleWindow(
            _display,
            root,
            x,
            y,
            width, 
            height,
            1,
            BlackPixel(_display, screen),
            WhitePixel(_display, screen)
        );

        _currentX = x;
        _currentY = y;
        _currentWidth = width;
        _currentHeight = height;

        long emitMasks =  (
                KeyPressMask |
                KeyReleaseMask |
                ButtonPressMask |
                ButtonReleaseMask |
                PointerMotionMask |
                StructureNotifyMask |
                FocusChangeMask
        );

        XSelectInput(
            _display,
            _window,
            emitMasks
        );

        XTextProperty prop;
        char* cString = const_cast<char*>(title.c_str());
        Xutf8TextListToTextProperty(_display, &cString, 1, XUTF8StringStyle, &prop);

        XSetWMName(_display, _window, &prop);
        XSetWMIconName(_display, _window, &prop);

        XFree(prop.value);

        Atom netWmName = XInternAtom(_display, "_NET_WM_NAME", False);
        Atom utf8String = XInternAtom(_display, "UTF8_STRING", False);

        XChangeProperty(
            _display,
            _window,
            netWmName,
            utf8String,
            8,
            PropModeReplace,
            reinterpret_cast<const unsigned char*>(title.c_str()),
            title.size()
        );
        
        XFlush(_display);

        _wmDelete = XInternAtom(_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(_display, _window, &_wmDelete, 1);

        _open = true;
    }

    X11Window::~X11Window() {
        XDestroyWindow(_display, _window);
        XCloseDisplay(_display);
    }
}
