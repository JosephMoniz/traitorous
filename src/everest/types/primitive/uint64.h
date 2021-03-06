#pragma once

#include <cstdint>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/unlawful/one.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/unlawful/subtract.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/traits/unlawful/divide.h>
#include <everest/traits/unlawful/remainder.h>
#include <everest/traits/unlawful/negate.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/square_root.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/bit_and.h>
#include <everest/traits/unlawful/bit_or.h>
#include <everest/traits/unlawful/bit_xor.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/copyable.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

template <>
class ZeroVal<uint64_t> final : public DefaultZeroVal<uint64_t> {};

template <>
class Semigroup<uint64_t> final : public DefaultSemigroup<uint64_t> {};

template <>
class Monoid<uint64_t> final : public DefaultMonoid<uint64_t> {};

template <>
class Subtractable<uint64_t> final : public DefaultSubtract<uint64_t> {};

template <>
class Multipliable<uint64_t> final : public DefaultMultipliable<uint64_t> {};

template <>
class Dividable<uint64_t> final : public DefaultDividable<uint64_t> {};

template <>
class Modulus<uint64_t> final : public DefaultModulus<uint64_t> {};

template <>
class Negation<uint64_t> final : public DefaultNegation<uint64_t> {};

template <>
class Bounded<uint64_t> final : public DefaultBounded<uint64_t> {};

template <>
class Eq<uint64_t> final : public DefaultEq<uint64_t> {};

template <>
class SquareRoot<uint64_t> final : public DefaultSquareRoot<uint64_t> {};

bool Equals(uint64_t lhs, uint64_t rhs) noexcept {
  return Eq<uint64_t>::Equals(lhs, rhs);
}

Predicate<uint64_t> Equals(uint64_t lhs) noexcept {
  return [=](uint64_t rhs) {
    return Eq<uint64_t>::Equals(lhs, rhs);
  };
}

template <>
class Ord<uint64_t> final : public DefaultOrd<uint64_t> {};

template <>
class BitAnd<uint64_t> final : public DefaultAnd<uint64_t> {};

template <>
class BitOr<uint64_t> final : public DefaultOr<uint64_t> {};

template <>
class BitXor<uint64_t> final : public DefaultXor<uint64_t> {};

template<>
class Hashable<uint64_t> final : public DefaultHashable<uint64_t> {};

template <>
class OneVal<uint64_t> final {
public:

  static constexpr bool exists = true;

  static constexpr uint64_t One() noexcept { return 1; }

};

template<>
class Fundamental<uint64_t> final {
public:
  static constexpr bool exists = true;
};

template<>
class Copyable<uint64_t> final {
public:

  static constexpr bool exists = true;

  static uint64_t Copy(uint64_t n) noexcept {
    return n;
  }

};

template <>
class Shows<uint64_t> final {
public:

  static constexpr bool exists = true;

  static size_t NumDigits(uint64_t number) noexcept {
    if (number < 10u) return 1;
    if (number < 100u) return 2;
    if (number < 1000u) return 3;
    if (number < 10000u) return 4;
    if (number < 100000u) return 5;
    if (number < 1000000u) return 6;
    if (number < 10000000u) return 7;
    if (number < 100000000u) return 8;
    if (number < 1000000000u) return 9;
    if (number < 10000000000u) return 10;
    if (number < 100000000000u) return 11;
    if (number < 1000000000000u) return 12;
    if (number < 10000000000000u) return 13;
    if (number < 100000000000000u) return 14;
    if (number < 1000000000000000u) return 15;
    if (number < 10000000000000000u) return 16;
    if (number < 100000000000000000u) return 17;
    if (number < 1000000000000000000u) return 18;
    if (number < 10000000000000000000u) return 19;
    return 20;
  }

  static String Show(uint64_t number) noexcept {
    auto size     = NumDigits(number);
    auto offset   = size;
    auto capacity = size + 1;
    auto memory   = MutableMemory<char>(capacity);
    auto pointer  = memory.MutablePointer();
    for (auto i = size; i; i--) {
      pointer[--offset] = (char) (number % 10) + '0';
      number /= 10;
    };
    pointer[size] = '\0';
    return String(std::move(memory), size, capacity);
  }

};

template<>
class Hexable<uint64_t> final {
public:

  static constexpr bool exists = true;

  static String ToHex(uint64_t value) noexcept {
    return ToHexFromLittleEndianBytePointer((unsigned char*) &value, sizeof(uint64_t));
  }

};

}

