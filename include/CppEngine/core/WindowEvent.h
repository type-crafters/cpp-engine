#pragma once
#include <cppengine/core/Base.h>
#include <variant>

namespace cppengine {
    enum class WindowEvent {
        CLOSE,
        RESIZE,
        MOVE,
        FOCUS,
        BLUR,
        KEYDOWN,
        KEYUP,
        MOUSEDOWN,
        MOUSEUP,
        MOUSEMOVE
    };

    enum class MouseButton : ubyte {
        NONE = 0, 
        LEFT = 1 << 0,
        MIDDLE = 1 << 1,
        RIGHT = 1 << 2,
        BROWSER_BACK = 1 << 3,
        BROWSER_FORWARD = 1 << 4
    };

    inline MouseButton operator|(MouseButton a, MouseButton b) {
        return static_cast<MouseButton>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline MouseButton operator&(MouseButton a, MouseButton b) {
        return static_cast<MouseButton>(static_cast<int>(a) & static_cast<int>(b));
    }

    struct CloseEventData { };

    struct ResizeEventData {
        int width;
        int height;
    };

    struct MoveEventData {
        int x;
        int y;
    };

    struct FocusEventData { };

    struct BlurEventData { };

    struct KeyboardEventData {
        int key;
    };

    struct MouseEventData {
        MouseButton trigger;
        MouseButton buttons;
        int clientX;
        int clientY;
    };

    template<WindowEvent E>
    struct EventDataType;

    template<>
    struct EventDataType<WindowEvent::CLOSE> {
        using type = CloseEventData;
    };

    template<>
    struct EventDataType<WindowEvent::RESIZE> {
        using type = ResizeEventData;
    };

    template<>
    struct EventDataType<WindowEvent::MOVE> {
        using type = MoveEventData;
    };

    template<>
    struct EventDataType<WindowEvent::FOCUS> {
        using type = FocusEventData;
    };

    template<>
    struct EventDataType<WindowEvent::BLUR> {
        using type = BlurEventData;
    };

    template<>
    struct EventDataType<WindowEvent::KEYDOWN> {
        using type = KeyboardEventData;
    };

    template<>
    struct EventDataType<WindowEvent::KEYUP> {
        using type = KeyboardEventData;
    };

    template<>
    struct EventDataType<WindowEvent::MOUSEDOWN> {
        using type = MouseEventData;
    };

    template<>
    struct EventDataType<WindowEvent::MOUSEUP> {
        using type = MouseEventData;
    };

    template<>
    struct EventDataType<WindowEvent::MOUSEMOVE> {
        using type = MouseEventData;
    };

    using EventData = std::variant<
        CloseEventData,
        ResizeEventData,
        MoveEventData,
        FocusEventData,
        BlurEventData,
        KeyboardEventData,
        MouseEventData
    >;
}