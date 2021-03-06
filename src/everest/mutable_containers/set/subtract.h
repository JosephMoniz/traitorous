#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class Subtractable<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSet<T> Subtract(const MutableSet<T>& lhs, const MutableSet<T>& rhs) noexcept {
    return lhs.Subtract(rhs);
  }

};

}