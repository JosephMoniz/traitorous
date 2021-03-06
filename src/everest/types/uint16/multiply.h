#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

class UInt16;

template <>
class Multipliable<UInt16> final {
public:

  static constexpr bool exists = true;

  static UInt16 Multiply(const UInt16 lhs, const UInt16 rhs) noexcept {
    return lhs.Multiply(rhs);
  }

};

}