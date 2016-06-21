#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Monad<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr MutableVector<B> FlatMap(F f, const MutableVector<T>& vector) noexcept {
    auto results = MutableVector<T>();
    ForEach(vector, [&](const T& item) {
      ForEach(f(item), [&](const T& inner) {
        PushInPlace(inner, results);
      });
    });
    return results;
  }

  template <class B>
  static constexpr MutableVector<B> Then(const MutableVector<T>& first, const MutableVector<B>& second) noexcept {
    return second;
  }

};

}