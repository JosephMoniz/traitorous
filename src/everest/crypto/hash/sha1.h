#pragma once

#include <openssl/sha.h>
#include <everest/types/string.h>
#include <everest/crypto/hash/sha1/sha1_digest.h>
#include <everest/crypto/hash/sha1/sha1_sink.h>

namespace everest {

Sha1Digest Sha1(const String& input) noexcept {
  Sha1Digest digest;
  SHA1((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

Sha1Sink Sha1() noexcept {
  return Sha1Sink();
}

}