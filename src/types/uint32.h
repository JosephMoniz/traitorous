#ifndef TRAITOROUS_TYPES_UINT32
#define TRAITOROUS_TYPES_UINT32 1

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
#include "string.h"

namespace traitorous {

template <>
class ZeroVal<uint32_t> : public DefaultZeroVal<uint32_t> {};

template <>
class Semigroup<uint32_t> : public DefaultSemigroup<uint32_t> {};

template <>
class Monoid<uint32_t> : public DefaultMonoid<uint32_t> {};

template <>
class Subtractable<uint32_t> : public DefaultSubtract<uint32_t> {};

template <>
class Multipliable<uint32_t> : public DefaultMultipliable<uint32_t> {};

template <>
class Dividable<uint32_t> : public DefaultDividable<uint32_t> {};

template <>
class Modulus<uint32_t> : public DefaultModulus<uint32_t> {};

template <>
class Negation<uint32_t> : public DefaultNegation<uint32_t> {};

template <>
class Bounded<uint32_t> : public DefaultBounded<uint32_t> {};

template <>
class Eq<uint32_t> : public DefaultEq<uint32_t> {};

constexpr inline bool Equals(uint32_t lhs, uint32_t rhs) noexcept {
  return Eq<uint32_t>::Equals(lhs, rhs);
}

inline Predicate<uint32_t> Equals(uint32_t lhs) noexcept {
  return [=](uint32_t rhs) {
    return Eq<uint32_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<uint32_t> : public DefaultOrd<uint32_t> {};

template <>
class BitAnd<uint32_t> : public DefaultAnd<uint32_t> {};

template <>
class BitOr<uint32_t> : public DefaultOr<uint32_t> {};

template <>
class BitXor<uint32_t> : public DefaultXor<uint32_t> {};

template<>
class Hashable<uint32_t> : public DefaultHashable<uint32_t> {};

template <>
class OneVal<uint32_t> {
public:

  static constexpr bool exists = true;

  static constexpr uint32_t One() noexcept { return 1; }

};

template <>
class Shows<uint32_t> {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(uint32_t number) noexcept {
    if (number < 10)         return 1;
    if (number < 100)        return 2;
    if (number < 1000)       return 3;
    if (number < 10000)      return 4;
    if (number < 100000)     return 5;
    if (number < 1000000)    return 6;
    if (number < 10000000)   return 7;
    if (number < 100000000)  return 8;
    if (number < 1000000000) return 9;
    return 10;
  }

  static const LocalString Show(uint32_t number) noexcept {
    auto size     = NumDigits(number);
    auto offset   = size;
    auto capacity = size + 1;
    auto memory   = LocalMemory<char>(capacity);
    auto pointer  = memory.MutablePointer();
    for (auto i = size; i; i--) {
      pointer[--offset] = (char) (number % 10) + '0';
      number /= 10;
    };
    pointer[capacity - 1] = '\0';
    return LocalString(std::move(memory), size);
  }

};

}

#endif
