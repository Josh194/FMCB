#pragma once

#include <cstdint>

enum struct Status : std::int32_t {
    kErrorInvalidParameter = -2,
    kErrorOverflow,
    kErrorSuccess
};

static_assert(static_cast<std::int32_t>(Status::kErrorSuccess) == 0, "Status enum not centered on 0");

extern Status status;