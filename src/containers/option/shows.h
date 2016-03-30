#pragma once

#include <containers/option.h>
#include <traits/unlawful/show.h>

namespace traitorous {

template <class T>
class Option;

template <class T>
class Shows<Option<T>> {
public:

  static constexpr bool exists = true;

  static const String Show(const Option<T>& n) noexcept {
    return Match(n,
      []()           { return String("None"); },
      [](const T& m) { return String("Some(") + Shows<T>::Show(m) + String(")"); }
    );
  }

};

}

