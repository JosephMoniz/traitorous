#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <types/string.h>

namespace traitorous {

template <class T>
class Shows {

  typedef Shows<T> Base;

public:

  static constexpr bool exists = false;

};

template <class T>
const String Show(const T& n) noexcept {
  return Shows<T>::Show(n);
}

}

#pragma clang diagnostic pop