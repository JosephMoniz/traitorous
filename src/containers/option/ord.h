#pragma once

#include "containers/option.h"
#include "traits/unlawful/ord.h"

namespace traitorous {

template <class T>
class Option;

template<class T>
class Ord<Option<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Ordering Compare(const Option<T> &lhs,
                                    const Option<T> &rhs) noexcept {
    return Match(lhs,
      [&rhs]() {
        return Match(rhs,
          []()           { return Ordering::EQUAL; },
          [](const T &x) { return Ordering::LESS; }
        );
      },
      [&rhs](const T &x) {
        return Match(rhs,
          []()             { return Ordering::GREATER; },
          [&x](const T &y) { return traitorous::Compare(x, y); }
        );
      }
    );
  }

  static constexpr const Option<T>& Min(const Option<T> &lhs,
                                        const Option<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::GREATER)
      ? rhs
      : lhs;
  }

  static constexpr const Option<T>& Max(const Option<T> &lhs,
                                        const Option<T> &rhs) noexcept
  {
    return (Compare(lhs, rhs) == Ordering::LESS)
      ? rhs
      : lhs;
  }

};

}
