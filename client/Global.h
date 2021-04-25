#pragma once

#include <cstdint>

// ? Shouldn't "#pragma once" negate the need for extern?
namespace api_global {
    extern void* fileHandle;

    extern std::int32_t bufferSize;
}