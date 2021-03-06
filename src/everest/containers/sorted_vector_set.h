#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/strings/string_joiner.h>

namespace everest {

template <class T>
class SortedVectorSet final {

  MutableSortedVectorSet<T> _set;

public:

  SortedVectorSet() noexcept : _set() { }

  SortedVectorSet(MutableSortedVectorSet&& set) noexcept : _set(std::move(set)) { }

  template <class U>
  Option<const T*> Find(const U& item) const noexcept {
    return _set.Find(item);
  }

  bool Contains(const T& item) const noexcept {
    return _set.Contains(item);
  }

  const T* Pointer() const noexcept {
    return _set.Pointer();
  }

  size_t Length() const noexcept {
    return _set.Length();
  }

  bool IsEmpty() const noexcept {
    return _set.IsEmpty();
  }

  template <class F>
  void ForEach(F function) const noexcept {
    return _set.ForEach(function);
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("SortedVectorSet(")
      .Add(StringJoiner(", ").Join(*this))
      .Add(")")
      .Build();
  }

  bool Equals(const SortedVectorSet<T>& other) const noexcept {
    return _set.Equals(other._set);
  }

  template <class F, class B = typename std::result_of<F(T)>::type>
  SortedVectorSet<B> Map(F f) const noexcept {
    return SortedVectorSet<B>(_set.Map(f));
  }

  SortedVectorSet<T> Add(const SortedVectorSet<T>& other) const noexcept {
    return SortedVectorSet<T>(_set.Add(other._set));
  }

  SortedVectorSet<T> Intersect(const SortedVectorSet<T>& other) const noexcept {
    return SortedVectorSet<T>(_set.Intersect(other._set));
  }

  SortedVectorSet<T> Subtract(const SortedVectorSet<T>& other) const noexcept {
    return SortedVectorSet<T>(_set.Subtract(other._set));
  }

  static SortedVectorSet<T> Zero() noexcept {
    return SortedVectorSet<T>();
  }

};

}