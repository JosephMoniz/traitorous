#pragma once

#include <everest/containers/array.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Containable<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const T& item, const Array<T, S>& array) noexcept {
    return array.Contains(item);
  }

};

}
