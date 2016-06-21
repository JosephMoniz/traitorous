#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

template<class T>
class MutableVector;

template<class T>
class Hexable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static String ToHex(const MutableVector<T>& vector) noexcept {
    return ToHexFromBigEndianBytePointer((unsigned char*) &vector, Length(vector));
  }

};

}