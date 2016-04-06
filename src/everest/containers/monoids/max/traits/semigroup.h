#pragma once

#include <everest/containers/monoids/max_monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class T>
class Semigroup<MaxMonoid<T>> {
public:

  static constexpr bool exists = true;

  static constexpr MaxMonoid<T> Add(const MaxMonoid<T>& lhs,
                                    const MaxMonoid<T>& rhs) noexcept
  {
    switch (Ord<T>::Compare(lhs.Value(), rhs.Value())) {
      case Ordering::LESS:    return rhs;
      case Ordering::GREATER: return lhs;
      case Ordering::EQUAL:   return lhs;
    }
  }

};

}