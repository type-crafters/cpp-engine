# Window API

CppEngine's Window API provides a platform-independent way of creating and interacting with windows. 

## Source code

### Header files:

- [Window.h](/include/cppengine/core/Window.h)
- [WindowEvent.h](/include/cppengine/core/WindowEvent.h)
- [Win32Window.h](/include/cppengine/platform/win32/Win32Window.h)

### Implementation files:

- [Win32Window.cpp](/src/cppengine/platform/win32/Win32Window.cpp)

## Specification

### Constants

| Type | Name | Description |
| --- | --- | --- |
| `int` | `CENTER_X` | Arbitrary integer that expresses intent to center a window horizontally on the monitor. |
| `int` | `CENTER_Y` | Arbitrary integer that expresses intent to center a window vertically on the monitor. |
| `int` | `SCREEN_WIDTH` | Computed integer value that resolves to the number of pixels per row on the monitor. |
| `int` | `SCREEN_HEIGHT` | Computed integer value that resolves to the number of pixels per column on the monitor. |

### Public constructors

| Signature | Description |
| --- | --- | 
| `Window(string title, int x, int y, int width, int height)` | Creates a window with a specified title, placement, and dimensions. |

### Public methods

| Type | Name | Description |
| --- | --- | --- |
| `string` | `getTitle()` | Retrieves the window's current title. |
| `void` | `setTitle(string title)` | Sets the window's title to a new string value. |
| `int` | `getX()` | Retrieves the horizontal coordinate of the window's top-left corner. |
| `void` | `setX(int x)` | Sets the horizontal coordinate of the window's top-left corner to a new integer value. |
| `int` | `getY()` | Retrieves the vertical coordinate of the window's top-left corner. |
| `void` | `setY(int y)` | Sets the vertical coordinate of the window's top-left corner to a new integer value. |
| `int` | `getWidth()` | Retrieves the window's current width in pixels. |
| `void` | `setWidth(int width)` | Sets the window's width to a new integer value. |
| `int` | `getHeight()` | Retrieves the window's height in pixels. |
| `void` | `setHeight(int height)` | Sets the window's height to a new integer value. |
| `int` | `getClientWidth()` | Retrieves the width of the window's operable area in pixels. |
| `int` | `getClientHeight()` | Retrieves the height of the window's operable area in pixels. |
| `bool` | `isOpen()` | Returns true if the window has already been created and no closing message has been posted. |
| `void` | `setDesktopIcon(string abspath)` | Sets the window's desktop icon to the image file at the location provided by `abspath`. |
| `void` | `setTitleBarIcon(string abspath)` | Sets the window's title bar icon to the image file at the location provided by `abspath`. |
| `void` | `emitEvent<WindowEvent E>(EventData& data)` | Emits an event of type `E`, potentially with data adhering to `data`'s  type to all listeners attached to the event type. |
| `void` | `addEventListener<WindowEvent E>(Fn&& fn)` | Subscribes a function object of type `Fn` to the window's listener registry, to be called when any event of type `E` is emitted by the window. |
| `void` | `display()` | Shows the window on the screen once it's created. |
| `void` | `processEvents()` | Initiates the communication between the window's internal message loop and the API's publish/subscribe event system. |