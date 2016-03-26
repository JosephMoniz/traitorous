#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_TAKEABLE
#define TRAITOROUS_TRAITS_TAKEABLE 1

#include <functional>

#include "functions/types.h"

namespace traitorous {

template <class T>
class Takeable {

  typedef Takeable<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr inline T Take(const T& n, size_t s) noexcept {
    return Base::Take(n, s);
  }

  template <class F, class N>
  static constexpr inline F TakeWhile(const F& n, Predicate<const N&> p) noexcept {
    return Base::TakeWhile(n, p);
  }

};

template <class T>
constexpr inline T Take(const T& n, size_t s) noexcept {
  return Takeable<T>::Take(n, s);
}

template <class F, class T>
constexpr inline F TakeWhile(const F& n, Predicate<const T&> p) noexcept {
  return Takeable<F>::TakeWhile(n, p);
}

}

#endif

#pragma clang diagnostic pop
