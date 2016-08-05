#pragma once

#include <everest/types/string.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/one.h>

namespace everest {

template<class T>
class GCounter final {

  T _value;

public:

  GCounter() noexcept : _value(ZeroVal<T>::Zero()) { }

  GCounter(const T& number) noexcept : _value(number) { }

  GCounter(const GCounter<T>& other) noexcept : _value(other._value) { }

  GCounter(GCounter<T>&& other) noexcept : _value(std::move(other._value)) { }

  GCounter<T> Increment() const noexcept {
    return GCounter(_value + OneVal<T>::One());
  }

  GCounter<T> IncrementBy(const T& number) const noexcept {
    return GCounter(_value + number);
  }

  T Value() const noexcept {
    return _value;
  }

};

template<class T>
class Shows<GCounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const GCounter<T>& counter) noexcept {
    return String("GCounter(") + Shows<T>::Show(counter.Value()) + String(")");
  }

};

template<class T>
class Eq<GCounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GCounter<T>& lhs, const GCounter<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template<class T>
class ZeroVal<GCounter<T>> final {
public:

  static constexpr bool exists = true;

  static GCounter<T> Zero() {
    return GCounter(Bounded<T>::MinValue());
  }

};

template<class T>
class Semigroup<GCounter<T>> final {
public:

  static constexpr bool exists = true;

  static GCounter<T> Add(const GCounter<T>& lhs, const GCounter<T>& rhs) noexcept {
    return GCounter(Ord<T>::Max(lhs.Value(), rhs.Value()));
  }

};

template<class T>
class Monoid<GCounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
