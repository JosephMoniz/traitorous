#pragma once

#include <stddef.h>
#include <string.h>
#include <everest/memory/mutable_memory.h>
#include <everest/strings/string.h>

namespace everest {

class MutableBitSet final {

  MutableMemory<int> _bits;

  Size _size;
  
public:

  static constexpr int intSize = sizeof(int) * 8;

  MutableBitSet() noexcept : MutableBitSet(32) { }

  MutableBitSet(Size size) noexcept : _size(size) {
    auto chunks = sizeToChunks(size);
    _bits       = MutableMemory<int>(chunks);
    memset(_bits.MutablePointer(), 0, chunks.Value());
  }

  MutableBitSet(const MutableBitSet& other) = delete;

  MutableBitSet(MutableBitSet&& other) noexcept : _bits(std::move(other._bits)),
                                                  _size(other._size) { }

  static Size sizeToChunks(Size size) noexcept {
    auto s = size.Value();
    return (s / MutableBitSet::intSize) + (s % MutableBitSet::intSize > 0 ? 1 : 0);
  }

  bool At(size_t offset) const noexcept {
    auto chunks = offset / intSize;
    auto bit    = offset % intSize;
    return _bits.Pointer()[chunks] && bit;
  }

  MutableBitSet& SetInPlace(size_t offset, bool value) noexcept {
    auto chunks  = offset / intSize;
    auto bit     = offset % intSize;
    auto pointer = _bits.MutablePointer();
    auto current = pointer[chunks];
    auto mask    = 1 << bit;
    if (value) {
      pointer[chunks] = current | mask;
    } else {
      pointer[chunks] = current & (~mask);
    }
    return *this;
  }

  const int* Pointer() const noexcept {
    return _bits.Pointer();
  }

  int* MutablePointer() noexcept {
    return _bits.MutablePointer();
  }

  MutableBitSet Copy() const noexcept {
    auto copy = MutableBitSet(_size);
    memcpy(copy.MutablePointer(), Pointer(), MutableBitSet::sizeToChunks(_size));
    return copy;
  }

  bool Contains(bool bit) const noexcept {
    auto pointer = Pointer();
    auto chunks  = MutableBitSet::sizeToChunks(_size);
    if (bit) {
      for (size_t i = 0; i < chunks; i++) {
        if (pointer[i] != 0) {
          return true;
        }
      }
      return false;
    } else {
      for (size_t i = 0; i < chunks; i++) {
        if (pointer[i] != 0xFF) {
          return true;
        }
      }
      return false;
    }
  }

  size_t Length() const noexcept {
    return _size;
  }

  bool IsEmpty() const noexcept {
    return !Contains(true);
  }

  template <class F>
  void ForEach(F function) const noexcept {
    auto pointer = Pointer();
    auto bits    = Length();
    auto eChunks = (bits / MutableBitSet::intSize);
    auto rBits   = bits % MutableBitSet::intSize;
    auto chunks  = eChunks + (rBits > 0 ? 1 : 0);
    auto highBit = 1 << (MutableBitSet::intSize - 1);
    for (size_t i = 0; i < eChunks; i++) {
      for (size_t j = 0; j < MutableBitSet::intSize; j++) {
        function(((pointer[i] << j) & highBit) != 0);
      }
    }
    if (chunks != eChunks) {
      for (size_t j = (MutableBitSet::intSize - rBits); j < MutableBitSet::intSize; j++) {
        function(((pointer[eChunks] << j) & highBit) != 0);
      }
    }
  }

  String Show() const noexcept {
    auto out = String("MutableBitSet(");
    ForEach([&](bool bit) {
      out = std::move(out) + String((bit ? "1" : "0"));
    });
    return std::move(out) + String(")");
  }
  
};

}
