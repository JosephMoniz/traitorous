#pragma once

#include <everest/containers/option.h>
#include <everest/traits/lawful/monad_plus.h>

namespace everest {

template <class T>
class Option;

template <class T>
class MonadPlus<Option<T>> final {
public:

  static constexpr bool exists = true;

  static constexpr Option<T> MPlus(const Option<T>& lhs,
                                   const Option<T>& rhs) noexcept
  {
    return Match(lhs,
      [&rhs]()           { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }

};

}
