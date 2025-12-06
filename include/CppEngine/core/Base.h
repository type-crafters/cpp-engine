#pragma once
#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

// type aliases
using std::string;
using ubyte = uint8_t;
using sbyte = int8_t;

template<typename... Args>
using Optional = std::optional<Args...>;

template<typename... Args>
using Vector = std::vector<Args...>; 

template<typename... Args>
using List = std::list<Args...>; 

template<typename... Args>
using Map = std::map<Args...>; 

template<typename... Args>
using HashMap = std::unordered_map<Args...>; 

template<typename... Args>
using Function = std::function<Args...>;