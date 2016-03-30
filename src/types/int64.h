#pragma once

#include <cstdint>
#include <functional>

#include "traits/unlawful/eq.h"
#include "traits/unlawful/ord.h"
#include "traits/unlawful/bounded.h"
#include "traits/unlawful/one.h"
#include "traits/lawful/monoid.h"
#include "traits/unlawful/subtract.h"
#include "traits/unlawful/multiply.h"
#include "traits/unlawful/divide.h"
#include "traits/unlawful/remainder.h"
#include "traits/unlawful/negate.h"
#include "traits/unlawful/bit_and.h"
#include "traits/unlawful/bit_or.h"
#include "traits/unlawful/bit_xor.h"
#include "traits/unlawful/shift_left.h"
#include "traits/unlawful/shift_right.h"
#include "traits/unlawful/show.h"
#include "traits/unlawful/hashable.h"
#include "functions/types.h"

namespace traitorous {

template <>
class ZeroVal<int64_t> : public DefaultZeroVal<int64_t> {};

template <>
class Semigroup<int64_t> : public DefaultSemigroup<int64_t> {};

template <>
class Monoid<int64_t> : public DefaultMonoid<int64_t> {};

template <>
class Subtractable<int64_t> : public DefaultSubtract<int64_t> {};

template <>
class Multipliable<int64_t> : public DefaultMultipliable<int64_t> {};

template <>
class Dividable<int64_t> : public DefaultDividable<int64_t> {};

template <>
class Modulus<int64_t> : public DefaultModulus<int64_t> {};

template <>
class Negation<int64_t> : public DefaultNegation<int64_t> {};

template <>
class Bounded<int64_t> : public DefaultBounded<int64_t> {};

template <>
class Eq<int64_t> : public DefaultEq<int64_t> {};

constexpr inline bool Equals(int64_t lhs, int64_t rhs) noexcept {
  return Eq<int64_t>::Equals(lhs, rhs);
}

inline Predicate<int64_t> Equals(int64_t lhs) noexcept {
  return [=](int64_t rhs) {
    return Eq<int64_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<int64_t> : public DefaultOrd<int64_t> {};

template <>
class BitAnd<int64_t> : public DefaultAnd<int64_t> {};

template <>
class BitOr<int64_t> : public DefaultOr<int64_t> {};

template <>
class BitXor<int64_t> : public DefaultXor<int64_t> {};

template<>
class Hashable<int64_t> : public DefaultHashable<int64_t> {};

template <>
class OneVal<int64_t> {
public:

  static constexpr bool exists = true;

  static constexpr int64_t One() noexcept { return 1; }

};

template <>
class Shows<int64_t> {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(int64_t number) noexcept {
    if (number < -1000000000000000000) return 20;
    if (number < -100000000000000000) return 19;
    if (number < -10000000000000000) return 18;
    if (number < -1000000000000000) return 17;
    if (number < -100000000000000) return 16;
    if (number < -10000000000000) return 15;
    if (number < -1000000000000) return 14;
    if (number < -100000000000) return 13;
    if (number < -10000000000) return 12;
    if (number < -1000000000) return 11;
    if (number < -100000000) return 10;
    if (number < -10000000) return 9;
    if (number < -1000000) return 8;
    if (number < -100000) return 7;
    if (number < -10000) return 6;
    if (number < -1000) return 5;
    if (number < -100) return 4;
    if (number < -10) return 3;
    if (number < 0) return 2;
    if (number < 10) return 1;
    if (number < 100) return 2;
    if (number < 1000) return 3;
    if (number < 10000) return 4;
    if (number < 100000) return 5;
    if (number < 1000000) return 6;
    if (number < 10000000) return 7;
    if (number < 100000000) return 8;
    if (number < 1000000000) return 9;
    if (number < 10000000000) return 10;
    if (number < 100000000000) return 11;
    if (number < 1000000000000) return 12;
    if (number < 10000000000000) return 13;
    if (number < 100000000000000) return 14;
    if (number < 1000000000000000) return 15;
    if (number < 10000000000000000) return 16;
    if (number < 100000000000000000) return 17;
    if (number < 1000000000000000000) return 18;
    return 19;
  }

  static const String Show(int64_t number) noexcept {
    auto signSpace = number < 0 ? 1 : 0;
    auto size      = NumDigits(number);
    auto offset    = size;
    auto capacity  = size + 1;
    auto memory    = Memory<char>(capacity);
    auto pointer   = memory.MutablePointer();
    auto unsignedN = number & 0x7FFFFFFF;
    for (size_t i = size; i - signSpace; i--) {
      pointer[--offset] = (char) (unsignedN % 10) + '0';
      unsignedN /= 10;
    };
    if (signSpace) {
      pointer[0] = '-';
    }
    pointer[capacity - 1] = '\0';
    return String(std::move(memory), size);
  }

};

}

