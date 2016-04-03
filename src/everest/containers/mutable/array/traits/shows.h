#pragma once

#include <everest/containers/mutable/mutable_array.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/types/string.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Shows<MutableArray<T, S>> {
public:

  static constexpr bool exists = true;

  static const String Show(const MutableArray<T, S>& array) noexcept {
    auto out = String("MutableArray(");
    for (size_t i = 0; i < S; i ++) {
      out = out + Shows<T>::Show(array.Pointer()[i]) + String(", ");
    }
    return Take(out, out.Length() - 2) + String(")");
  }

};

}