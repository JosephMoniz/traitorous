#pragma once

#include <string>

#include <stddef.h>

#include "containers/array.h"
#include "traits/lawful/semigroup.h"

namespace traitorous {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Semigroup<Array<T, S>> {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static constexpr SharedArray<T, S + Rs> Add(const Array<T, S>& lhs,
                                              const Array<T, Rs>& rhs) noexcept
  {
    auto newArray = MakeSharedArray<T, Ns>();
    for (size_t i = 0; i < S; i++) {
      newArray->MutablePointer()[i] = lhs.Pointer()[i];
    }
    for (size_t i = 0; i < Rs; i++) {
      newArray->MutablePointer()[i + S] = rhs.Pointer()[i];
    }
    return newArray;
  }

};

}
