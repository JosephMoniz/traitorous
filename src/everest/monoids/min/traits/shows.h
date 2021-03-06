#pragma once

#include <everest/strings/string.h>
#include <everest/monoids/min_monoid.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T>
class MinMonoid;

template<class T>
class Shows<MinMonoid<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MinMonoid<T>& monoid) noexcept {
    return monoid.Show();
  }

};

}