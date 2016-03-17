#ifndef TRAITOROUS_CONTAINERS_SHARED_H
#define TRAITOROUS_CONTAINERS_SHARED_H

#include "types/uint32.h"

namespace traitorous {

template<class T>
class Shared {
private:

  uint32_t *_count;
  T *_pointer;

public:

  Shared(T* external) : _pointer(external) {
    if (_pointer != nullptr) {
      _count = new uint32_t;
      *_count = 1;
    } else {
      _count = nullptr;
    }
  }

  Shared(T* external, uint32_t* count) : _pointer(external), _count(count) {
    if (_count != nullptr) {
      (*_count)++;
    }
  }

  Shared(const Shared<T>& other) : _count(other._count), _pointer(other._pointer) {
    if (_count != nullptr) {
      (*_count)++;
    }
  }

  Shared(Shared<T>&& other) : _count(std::move(other._count)), _pointer(std::move(other._pointer)) {
    other._count   = nullptr;
    other._pointer = nullptr;
  }

  Shared& operator=(const Shared<T>& other) {
    _count   = other._count;
    _pointer = other._pointer;
    if (_count != nullptr) {
      (*_count)++;
    }
    return *this;
  }

  ~Shared() {
    if (_count != nullptr && --(*_count) == 0) {
      delete _pointer;
      delete _count;
    }
  }

  T* operator->() const noexcept {
    return _pointer;
  }

  T& operator*() const noexcept {
    return *_pointer;
  }

  T* Pointer() const noexcept {
    return _pointer;
  }

  uint32_t* Counter() const noexcept {
    return _count;
  }

};

template<class T, class ...As>
Shared<T> MakeShared(As&&... args) {
  return Shared<T>(new T(args...));
}

template<class T, class U>
Shared<U> DynamicSharedCast(const Shared<T>& shared) {
  U* internal = dynamic_cast<U*>(shared.Pointer());
  return Shared<U>(internal, shared.Counter());
};

}

#endif
