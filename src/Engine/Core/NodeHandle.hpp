#pragma once

#include <cstdint>

namespace Engine {

struct NodeHandle {
  uint32_t index = 0;
  uint32_t generation = 0;

  bool IsValid() const { return generation != 0; }
  bool operator==(const NodeHandle &other) const = default;
};

} // namespace Engine
