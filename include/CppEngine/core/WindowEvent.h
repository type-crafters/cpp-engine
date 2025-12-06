#pragma once
#include <CppEngine/core/Base.h>
#include <variant>

namespace CppEngine {
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