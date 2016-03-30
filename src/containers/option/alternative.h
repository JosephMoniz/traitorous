#pragma once

#include "containers/option.h"
#include "traits/lawful/alternative.h"

namespace traitorous {

template <class T>
class Option;

template <class T>
class Alternative<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Option<T> Alt(const Option<T>& lhs,
                                 const Option<T>& rhs) noexcept
  {
    return Match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }

};

}
