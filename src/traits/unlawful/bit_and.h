#ifndef TRAITOROUS_TRAITS_BITAND
#define TRAITOROUS_TRAITS_BITAND 1

namespace traitorous {

template <class T>
struct bit_and {
  // T and()
  static constexpr bool exists = false;
};

template <class T>
struct default_and {
  static constexpr T apply(const T& lhs, const T& rhs) noexcept {
    return lhs & rhs;
  }
  static constexpr bool exists = true;
};

template <class T, class = typename std::enable_if<bit_and<T>::exists>::type>
constexpr inline T b_and(const T& lhs, const T& rhs) noexcept {
  return bit_and<T>::apply(lhs, rhs);
}

}

#endif