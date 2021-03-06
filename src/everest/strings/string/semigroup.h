#pragma once

#include <everest/strings/string.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/strings/mutable_string/semigroup.h>

namespace everest {

class String;

template<>
class Semigroup<String> final {
public:

  static constexpr bool exists = true;

  static String Add(const String& lhs, const String& rhs) noexcept {
    return lhs.Add(rhs);
  }

  static String Add(String&& lhs, const String& rhs) noexcept {
    return String(Semigroup<MutableString>::Add(std::move(lhs._wrapped), rhs._wrapped));
  }

};

}