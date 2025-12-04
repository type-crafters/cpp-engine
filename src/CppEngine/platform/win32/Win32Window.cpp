#include <stdexcept>
#include <windows.h> 
#include <CppEngine/platform/win32/Win32Window.h>


namespace CppEngine {
    const int Window::SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
    const int Window::SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
    const WCHAR* Win32Window::_WINDOW_CLASSNAME = L"Win32Window::WindowClass";

    Win32Window::Win32Window(string title, int x, int y, int width, int height) : Window(title, x, y, width, height) {
        int titleSize = MultiByteToWideChar(CP_UTF8, NULL, title.c_str(), -1, nullptr, 0);
        std::wstring ws(titleSize, L'\0');
        MultiByteToWideChar(CP_UTF8, NULL, title.c_str(), -1, &ws[0], titleSize);
        const WCHAR* wideTitle = ws.c_str();

        WNDCLASSEX windowClass{};
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.lpszClassName = _WINDOW_CLASSNAME;
        windowClass.lpfnWndProc = DefWindowProc;

        ATOM windowClassId = RegisterClassEx(&windowClass);

        if (!windowClassId) {
            throw std::runtime_error("Class registration has failed.");
        }

        DWORD windowStyles = WS_OVERLAPPEDWINDOW;
        RECT windowSize{0, 0, width, height};
        AdjustWindowRect(&windowSize, windowStyles, false);

        int windowWidth = windowSize.right - windowSize.left;
        int windowHeight = windowSize.bottom - windowSize.top;

        if (x == CENTER_X) {
            x = (SCREEN_WIDTH - windowWidth) / 2;
        }

        if (y == CENTER_Y) {
            y = (SCREEN_HEIGHT - windowHeight) / 2;
        }
        
        _handle = CreateWindowEx(
            NULL,
            _WINDOW_CLASSNAME, 
            wideTitle, 
            windowStyles, 
            x, 
            y, 
            windowWidth, 
            windowHeight, 
            NULL, 
            NULL, 
            NULL, 
            NULL
        );

        if (!_handle) {
            throw std::runtime_error("Window handle creation has failed.");
        }
    }

    void Win32Window::show() {
        ShowWindow(static_cast<HWND>(_handle), SW_SHOW);
    }

    Win32Window::~Win32Window() {
        DestroyWindow(static_cast<HWND>(_handle));
    }
}