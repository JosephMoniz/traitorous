#ifndef TRAITOROUS_CONTAINERS_OPTION
#define TRAITOROUS_CONTAINERS_OPTION 1

#include <string>
#include <type_traits>

#include "core/tagged_union.h"

#include "meta/nth_arg.h"
#include "traits/alternative.h"
#include "traits/applicative.h"
#include "traits/containable.h"
#include "traits/container.h"
#include "traits/eq.h"
#include "traits/filterable.h"
#include "traits/foldable.h"
#include "traits/functor.h"
#include "traits/hashable.h"
#include "traits/monad.h"
#include "traits/monad_plus.h"
#include "traits/monoid.h"
#include "traits/ord.h"
#include "traits/semigroup.h"
#include "traits/show.h"
#include "traits/unwrappable.h"
#include "traits/zero.h"

namespace traitorous {

template <class T>
class option;

struct _none {} none_instance;

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
static constexpr R cata(const option<T>& o, N n, S s) noexcept;

template <class T>
class option : public tagged_union<T, _none> {
public:

  option(const T& val): tagged_union<T, _none>(val) {}

  option(size_t id, void* val): tagged_union<T, _none>(id, val) {}

  option(const option<T>& val): tagged_union<T, _none>(val) {}

  option(const option<T>&& val): tagged_union<T, _none>(val) {}

  constexpr inline size_t length() noexcept {
    return traitorous::length(*this);
  }

  constexpr inline bool is_empty() noexcept {
    return traitorous::is_empty(*this);
  }

  constexpr inline bool equals(const option<T> rhs) noexcept {
    return traitorous::equals(*this, rhs);
  }

  constexpr inline option<T> add(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return traitorous::add(lhs, rhs);
  }

  constexpr inline bool contains(const T& n) noexcept {
    return traitorous::contains(*this, n);
  }

  constexpr inline option<T> filter(std::function<bool(const T&)> p) noexcept {
    return traitorous::filter(*this, p);
  }

  constexpr inline T get_or_default(const T& d) noexcept {
    return traitorous::get_or_default(*this, d);
  }

  constexpr inline T get_or_else(std::function<T()> d) noexcept {
    return traitorous::get_or_else(*this, d);
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  constexpr inline option<B> map(F f) noexcept {
    return traitorous::map(f, *this);
  }

  template <class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  constexpr inline option<B> flat_map(F f) noexcept {
    return traitorous::flat_map(f, *this);
  }

  template <class A, class B = typename std::result_of<T(A)>::type>
  constexpr inline option<B> ap(const option<A>& a) noexcept {
    return traitorous::ap(*this, a);
  }

  template <class N, class S, class B = typename std::result_of<N()>::type>
  constexpr inline B cata(N n, S s) noexcept {
    return traitorous::cata(*this, n, s);
  }

};

template <class T>
option<T> some(const T& t) {
  return option<T>(t);
}

template <class T>
option<T> none() {
  return option<T>(typeid(_none).hash_code(), &none_instance);
}

template <class T,
          class N,
          class S,
          class R = typename std::result_of<N()>::type>
static constexpr R cata(const option<T>& o, N n, S s) noexcept {
  return (o.template is<_none>()) ? n() : s(o.template get<T>());
}

template <class T>
struct containable<option<T>> {
  static constexpr bool contains(const option<T>& f, const T& n) noexcept {
    return f.cata(
      []() { return false; },
      [&n](const T& m) { return n == m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct container<option<T>> {
  static constexpr size_t length(const option<T>& o) noexcept {
    return o.cata(
      [](){ return 0; },
      [](const T& n){ return 1; }
    );
  }
  static constexpr bool is_empty(const option<T>& o) noexcept {
    return o.cata(
      [](){ return true; },
      [](const T& n){ return false; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct eq<option<T>> {
  static constexpr bool equals(const option<T>& lhs,
                               const option<T>& rhs) noexcept
  {
    return lhs.cata(
      [&](){
        return rhs.cata(
          [](){ return true; },
          [](const T& y){ return false; }
        );
      },
      [&](const T& x){
        return rhs.cata(
          [](){ return false; },
          [&](const T& y){ return eq<T>::equals(x, y); }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct hashable<option<T>> {
  static constexpr int hash(const option<T>& o) noexcept {
    return cata(o,
      [](){ return 0; },
      [](const T& n) { return hashable<T>::hash(n); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct zero_val<option<T>> {
  static constexpr option<T> zero() { return none<T>(); }
  static constexpr bool exists = true;
};

template <class T>
struct semigroup<option<T>> {
  static constexpr option<T> add(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return lhs.cata(
      [&rhs]() { return rhs; },
      [&](const T& x) {
        return rhs.cata(
          [&lhs]() { return lhs; },
          [&](const T& y){ return some(semigroup<T>::add(x, y)); }
        );
      }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monoid<option<T>> {
  static constexpr bool exists = true;
};

template <class T>
struct filterable<option<T>> {
  static constexpr option<T> filter(const option<T>& n,
                                    std::function<bool(const T&)> p) noexcept
  {
    return n.cata(
      []() { return none<T>(); },
      [&](const T& m) { return p(m) ? n : none<T>(); }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct ord<option<T>> {

  static constexpr Ordering cmp(const option<T>& lhs,
                                const option<T>& rhs) noexcept
  {
    return lhs.cata(
      [&rhs]() {
        return rhs.cata(
          []() { return EQUAL; },
          [](const T& x) { return LESS; }
        );
      },
      [&rhs](const T& x) {
        return rhs.cata(
          []() { return GREATER; },
          [&x](const T& y) { return ord<T>::cmp(x, y); }
        );
      }
    );
  }

  static constexpr option<T> min(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return (ord<T>::cmp(lhs, rhs) == GREATER) ? rhs : lhs;
  }
  static constexpr option<T> max(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return (ord<T>::cmp(lhs, rhs) == LESS) ? rhs : lhs;
  }
  static constexpr bool exists = true;
};

template <class T>
struct functor<option<T>> {
  template <class F, class B = typename std::result_of<F(T)>::type>
  static constexpr option<B> map(F f, const option<T>& n) noexcept {
    return n.cata(
      []() { return none<B>(); },
      [&f](const T& n) { return some(f(n)); }
    );
  }
  static constexpr bool exists = true;
};

template <class F>
struct applicative<option<F>> {
  template <class A, class B = typename std::result_of<F(A)>::type>
  static constexpr option<B> ap(const option<F>& f, const option<A>& a) noexcept {
    return f >>= [&a](const F& fn) { return a.map(fn); };
  }
  static constexpr bool exists = true;
};

template <class T>
struct alternative<option<T>> {
  static constexpr option<T> alt(const option<T>& lhs,
                                 const option<T>& rhs) noexcept
  {
    return lhs.cata(
      [&rhs]() { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct foldable<option<T>> {
  static constexpr T fold(const option<T>& n) noexcept {
    return n.cata(
      []() { return zero_val<T>::zero(); },
      [&n](const T& m) { return m; }
    );
  }
  template <class M>
  static constexpr M foldMap(std::function<M(const T&)> f,
                             const option<T>& n) noexcept
  {
    return n.cata(
      []() { return zero_val<T>::zero(); },
      [&f](const T& m) { return f(m); }
    );
  }
  template <class B>
  static constexpr B foldr(std::function<B(const B&, const T&)> f,
                           const B& init,
                           const option<T>& n) noexcept
  {
    return n.cata(
      [&init]() { return init; },
      [&f](const T& m) { return m; }
    );
  }
  template <class B>
  static constexpr B foldl(std::function<B(const B&, const T&)> f,
                           const B& init,
                           const option<T>& n) noexcept
  {
    return n.cata(
      [&init]() { return init; },
      [&f](const T& m) { return m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct monad<option<T>> {
  template <class F,
            class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr option<B> flat_map(F f, const option<T>& m) noexcept {
    return m.cata(
      [&m]() { return none<B>(); },
      [&f](const T& t) { return f(t); }
    );
  }
  template <class B>
  static constexpr option<B>& then(const option<T>& m,
                                   const option<T>& n) noexcept
  {
    return n;
  }
  static constexpr bool exists = true;
};

template <class T>
struct monad_plus<option<T>> {
  static constexpr option<T>& mplus(const option<T>& lhs,
                                  const option<T>& rhs) noexcept
  {
    return lhs.cata(
      [&rhs]() { return rhs; },
      [&lhs](const T& n) { return lhs; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct unwrappable<option<T>> {
  static constexpr T get_or_else(const option<T>& n, std::function<T()> d) noexcept {
    return n.cata(
      [&d]() { return d(); },
      [](const T& m) { return m; }
    );
  }
  static constexpr T get_or_default(const option<T>& n, const T& d) noexcept {
    return n.cata(
      [&d]() { return d; },
      [](const T& m) { return m; }
    );
  }
  static constexpr bool exists = true;
};

template <class T>
struct shows<option<T>> {
  static const std::string show(const option<T>& n) noexcept {
    return n.cata(
      []() { return std::string("none"); },
      [](const T& n) { return std::string("some(") + shows<T>::show(n) + ")"; }
    );
  }
  static constexpr bool exists = true;
};

}

#endif
