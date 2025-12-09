# Documentation: CppEngine

CppEngine's documentation provides a wiki-like overview of its architecture, subsystems and integration in external projects.

## Contents

- API Reference
    - [System](/docs/api/System.md)
    - [Window](/docs/api/Window.md)

## Code style

### Naming conventions

The CppEngine project adheres to certain naming conventions for code readability and clarity.

| Type | Convention | Example |
| --- | --- | --- |
| class/struct names | PascalCase | `class ClassName` |
| public/protected members | camelCase | `char totalPoints` |
| private members | _camelCase | `int _bufferSize ` |
| constant/readonly members | UPPER_CASE | `const int MAX_ITER` |
| enum members | UPPER_CASE | `PlayerState PlayerState::IDLE` |
| type aliases | PascalCase | `using Map = std::map<Args...>` |
| top-level functions | camelCase | `void createWindow()` |
| namespaces | lowercase | `namespace cppinput` |

### Type aliases

The following type aliases are declared inside the [<Base.h>](/include/cppengine/core/Base.h) header file, meaning they are available project-wide.

| Type | Alias | Description |
| --- | --- | --- |
| `std::string` | `string` | A dynamically sized, C++ style character sequence |
| `std::filesystem::path` | `path` | A platform-aware representation of filesystem paths, included in the <filesystem> header |
| `uint8_t` | `ubyte` | An unsigned 8-bit integer type included in the `<cstdint>` header |
| `int8_t` | `sbyte` | A signed 8-bit integer type included in the `<cstdint>` header |
| `std::optional<T,...>` | `Optional<T...>` | A representation of a value that can be either `T` or `std::nullopt`, included in the `<optional>` header |
| `std::vector<T,...>` | `Vector<T...>` | An ordered, low-overhead, memory-linear sequence of values of type `T` included in the `<vector>` header |
| `std::list<T,...>` | `List<T...>` | An ordered, doubly linked list of `T` nodes included in the `<list>` header |
| `std::map<K, V, ...>` | `Map<K, V, ...>` | An ordered, binary-tree-based implementation of a key-value collection included in the `<map>` header |
| `std::unordered_map<K, V, ...>` | `HashMap<K, V, ...>` | An unordered, hash-table-based implementation of a key-value collection included in the `<unordered_map>` header |
| `std::function<T(A...),...>` | `Function<T(A...), ...>` | A type-erased callable wrapper that can store and invoke any function object that takes `A...` arguments and returns a value of type `T` |

The docs will reference these aliases, rather than their underlying types, to maintain consistency and clarity across all examples.