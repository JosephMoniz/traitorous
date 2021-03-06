#pragma once

#include <everest/containers/option.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class T>
class Option;

template<class T>
class ZeroVal<Option<T>> final {
public:

  static constexpr bool exists = true;

  static Option<T> Zero() {
    return Option<T>::Zero();
  }

};

}

