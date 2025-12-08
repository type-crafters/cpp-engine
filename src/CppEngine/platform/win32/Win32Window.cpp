#include <stdexcept> 
#include <CppEngine/platform/win32/Win32Window.h>

namespace CppEngine {
    const int Window::SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
    const int Window::SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
    const string Win32Window::_WINDOW_CLASSNAME = "Win32Window::WindowClass";
    
    LRESULT CALLBACK Win32Window::_windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        Win32Window* window = nullptr;
        if (msg == WM_NCCREATE) {
            CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
            window = reinterpret_cast<Win32Window*>(cs -> lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) window);
        } else {
            window = reinterpret_cast<Win32Window*>(
                GetWindowLongPtr(hwnd, GWLP_USERDATA)
            );
        }

        if (window) {
            switch (msg) {
                case WM_CLOSE:
                    window->emitEvent<WindowEvent::CLOSE>({});
                    window -> _open = false;
                    return 0;
                case WM_SIZE:
                    window -> emitEvent<WindowEvent::RESIZE>({ 
                        LOWORD(lParam),
                        HIWORD(lParam)
                    });
                    return 0;
                case WM_SETFOCUS:
                    window -> emitEvent<WindowEvent::FOCUS>({});
                    return 0;
                case WM_KILLFOCUS:
                    window -> emitEvent<WindowEvent::BLUR>({});
                    return 0;
                case WM_KEYDOWN:
                    window -> emitEvent<WindowEvent::KEYDOWN>({ (int) wParam });
                    return 0;
                case WM_KEYUP:
                    window -> emitEvent<WindowEvent::KEYUP>({ (int) wParam });
                    return 0;
                case WM_DESTROY:
                    window -> _open = false;
                    PostQuitMessage(0);
                    return 0;
                case WM_NCDESTROY:
                    SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
                    window -> _open = false;
                    return 0;
            }
        }

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    string Win32Window::getTitle() {
        int titleLength = GetWindowTextLengthA(_handle);
        if (titleLength <= 0) {
            return "";
        }

        string title(titleLength + 1, '\0');
        int copyLength = GetWindowTextA(_handle, title.data(), titleLength + 1);
  
        title.resize(copyLength);
        return title;
    }


    void Win32Window::setTitle(string title) {
        SetWindowTextA(_handle, title.c_str());
    }

    int Win32Window::getX() {
        RECT rect;
        GetWindowRect(_handle, &rect);
        return rect.left;
    }

    void Win32Window::setX(int x) {
        RECT rect;
        GetWindowRect(_handle, &rect);

        SetWindowPos(
            _handle,
            nullptr,
            x,
            rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
    }

    int Win32Window::getY() {
        RECT rect;
        GetWindowRect(_handle, &rect);
        return rect.top;
    }

    void Win32Window::setY(int y) {
        RECT rect;
        GetWindowRect(_handle, &rect);

        SetWindowPos(
            _handle,
            nullptr,
            rect.left,
            y,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
    }

    int Win32Window::getWidth() {
        RECT rect;
        GetWindowRect(_handle, &rect);
        return rect.right - rect.left;
    }

    void Win32Window::setWidth(int width) {
        RECT rect;
        GetWindowRect(_handle, &rect);

        SetWindowPos(
            _handle,
            nullptr,
            rect.left,
            rect.top,
            width,
            rect.bottom - rect.top,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
    }

    int Win32Window::getHeight() {
        RECT rect;
        GetWindowRect(_handle, &rect);
        return rect.bottom - rect.top;
    }

    void Win32Window::setHeight(int height) {
        RECT rect;
        GetWindowRect(_handle, &rect);

        SetWindowPos(
            _handle,
            nullptr,
            rect.left,
            rect.top,
            rect.right - rect.left,
            height,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
    }

    bool Win32Window::isOpen() {
        return _open;
    }

    int Win32Window::getClientWidth() {
        RECT rect;
        GetClientRect(_handle, &rect);
        return rect.right - rect.left;
    }

    int Win32Window::getClientHeight() {
        RECT rect;
        GetClientRect(_handle, &rect);
        return rect.bottom - rect.top;
    }

    void Win32Window::setDesktopIcon(string abspath) {
        // @todo implement
    }

    void Win32Window::setTitleBarIcon(string abspath) {
        // @todo implement
    }

    // constructor and destructor
    Win32Window::Win32Window(string title, int x, int y, int width, int height) {

        WNDCLASSEXA windowClass{};
        windowClass.cbSize = sizeof(WNDCLASSEXA);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = Win32Window::_windowProc;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = GetModuleHandle(NULL);
        windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // @todo change
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        windowClass.lpszMenuName = NULL;
        windowClass.lpszClassName = _WINDOW_CLASSNAME.c_str();
        windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // @todo change


        ATOM windowClassId = RegisterClassExA(&windowClass);

        if (!windowClassId) {
            throw std::runtime_error("Class registration has failed.");
        }

        DWORD windowStyles = WS_OVERLAPPEDWINDOW;
        RECT windowSize{0, 0, width, height};
        AdjustWindowRectEx(&windowSize, windowStyles, false, 0);

        int windowWidth = windowSize.right - windowSize.left;
        int windowHeight = windowSize.bottom - windowSize.top;

        if (x == CENTER_X) {
            x = (SCREEN_WIDTH - windowWidth) / 2;
        }

        if (y == CENTER_Y) {
            y = (SCREEN_HEIGHT - windowHeight) / 2;
        }
        
        _handle = CreateWindowExA(
            NULL,
            _WINDOW_CLASSNAME.c_str(), 
            title.c_str(), 
            windowStyles, 
            x, 
            y, 
            windowWidth, 
            windowHeight, 
            NULL, 
            NULL, 
            GetModuleHandle(NULL),
            this
        );

        if (!_handle) {
            throw std::runtime_error("Window handle creation has failed.");
        }

        _open = true;
    }

    Win32Window::~Win32Window() {
        DestroyWindow(_handle);
    }

    void Win32Window::display() {
        ShowWindow(_handle, SW_SHOW);
        UpdateWindow(_handle);
    }

    void Win32Window::processEvents() {
        MSG msg{};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            // @todo notify engine on WM_QUIT
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
} 