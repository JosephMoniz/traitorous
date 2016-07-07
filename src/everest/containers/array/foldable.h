#pragma once

#include <everest/traits/lawful/foldable.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/containers/array.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Foldable<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  static T Fold(const Array<T, S>& array) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer(array);
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(std::move(memo), pointer[i]);
    }
    return memo;
  }

  template <class Fn, class M = typename std::result_of<Fn(T)>::type>
  static M FoldMap(Fn f, const Array<T, S>& array) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer(array);
    for (size_t i = 0; i < S; i++) {
      memo = Semigroup<T>::Add(std::move(memo), f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  static  B FoldR(Fn f, const B& init, const Array<T, S>& array) noexcept {
    auto memo    = init;
    auto pointer = Pointer(array);
    for (size_t i = S - 1; i; i--) {
      memo = f(std::move(memo), pointer[i]);
    }
    if (S > 0) {
      memo = f(std::move(memo), pointer[0]);
    }
    return memo;
  }

  template <class Fn, class B>
  static B FoldL(Fn f, const B& init, const Array<T, S>& array) noexcept {
    auto memo    = init;
    auto pointer = Pointer(array);
    for (size_t i = 0; i < S; i++) {
      memo = f(std::move(memo), pointer[i]);
    }
    return memo;
  }

};

}
