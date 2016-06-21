#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_filter.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class MutableFilter<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  template<class Predicate>
  static MutableVector<T>& FilterInPlace(Predicate predicate, MutableVector<T>& vector) noexcept {
    size_t passed = 0;
    auto pointer  = MutablePointer(vector._memory);
    auto length   = Length(vector);
    for (size_t i = 0; i < length; i++) {
      if (predicate(pointer[i])) {
        if (i != passed) {
          pointer[passed] = std::move(pointer[i]);
        }
        passed++;
      }
    }
    vector._length = passed;
    return vector;
  }

};

}