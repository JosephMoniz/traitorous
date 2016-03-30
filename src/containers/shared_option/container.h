#pragma once

#include "containers/option.h"
#include "traits/unlawful/container.h"

namespace traitorous {

template<class T>
using SharedOption = Shared<Option<T>>;

template <class T>
class Container<SharedOption<T>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const SharedOption<T>& o) noexcept {
    return Container<Option<T>>::Length(*o);
  }

  static constexpr bool IsEmpty(const SharedOption<T>& o) noexcept {
    return Container<Option<T>>::IsEmpty(*o);
  }

};

}
