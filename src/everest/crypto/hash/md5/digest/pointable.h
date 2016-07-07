#pragma once

#include <everest/crypto/hash/md5/md5_digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Md5Digest;

template<>
class Pointable<Md5Digest> final {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Md5Digest& digest) noexcept {
    return digest.Value();
  }

};

}