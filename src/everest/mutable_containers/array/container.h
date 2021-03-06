#pragma once

#include <everest/mutable_containers/mutable_array.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Container<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const MutableArray<T, S>& o) noexcept {
    return o.Length();
  }

  static bool IsEmpty(const MutableArray<T, S>& o) noexcept {
    return o.IsEmpty();
  }

};

}
