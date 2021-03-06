#pragma once

#include <everest/crypto/hash/md5/md5_digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Md5Digest;

template<>
class Hexable<Md5Digest> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const Md5Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Md5Digest::size);
  }

};

}