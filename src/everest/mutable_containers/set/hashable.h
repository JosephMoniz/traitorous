#pragma once

#include <everest/mutable_containers/mutable_set.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template<class T>
class MutableSet;

template <class T>
class Hashable<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const MutableSet<T>& set) noexcept {
    return set.Hash();
  }

};

}