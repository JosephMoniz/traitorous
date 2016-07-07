#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class Monoid<MutableSet<T>> final {
public:
  static constexpr bool exists = true;
};

}