#pragma once

#include <everest/test/bdd.h>
#include <everest/mutable_containers/mutable_sorted_vector_map.h>
#include <everest/mutable_containers/sorted_vector_map/all_traits.h>

namespace everest {

void MutableSortedVectorMapSpecification() {
  Describe("A MutableSortedVectorMap type", []() {
    Describe("of value {'one': 1, 'two': 2, 'three': 3, 'four': 4}", []() {
      auto subject = MutableSortedVectorMap<String, int>();
      PutInPlace(String("one"), 1, subject);
      PutInPlace(String("two"), 2, subject);
      PutInPlace(String("three"), 3, subject);
      PutInPlace(String("four"), 4, subject);
      It("Should render the correct mutable_string when called with Shows()", [&](){
        auto expected = String("MutableSortedVectorMap(one: 1, two: 2, four: 4, three: 3)");
        auto result   = Show(subject);
        AssertEquals(expected, result);
      });
      It("Should return false when called with Contains('zero')", [&]() {
        AssertFalse(Contains(String("zero"), subject));
      });
      It("Should return true when called with Contains('one')", [&]() {
        AssertTrue(Contains(String("one"), subject));
      });
      It("Should return true when called with Contains('two')", [&]() {
        AssertTrue(Contains(String("two"), subject));
      });
      It("Should return true when called with Contains('three')", [&]() {
        AssertTrue(Contains(String("three"), subject));
      });
      It("Should return true when called with Contains('four')", [&]() {
        AssertTrue(Contains(String("four"), subject));
      });
      It("Should return false when called with Contains('five')", [&]() {
        AssertFalse(Contains(String("five"), subject));
      });
      It("Should return nullptr when called with Get('zero')", [&]() {
        AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject).Get());
      });
      It("Should return 1 when called with Get('one')", [&]() {
        AssertEquals(1, GetInPlace(String("one"), subject).Get()[0]);
      });
      It("Should return 2 when called with Get('two')", [&]() {
        AssertEquals(2, GetInPlace(String("two"), subject).Get()[0]);
      });
      It("Should return 3 when called with Get('three')", [&]() {
        AssertEquals(3, GetInPlace(String("three"), subject).Get()[0]);
      });
      It("Should return 4 when called with Get('four')", [&]() {
        AssertEquals(4, GetInPlace(String("four"), subject).Get()[0]);
      });
      It("Should return nullptr when called with Get('five')", [&]() {
        AssertEquals<int>(nullptr, GetInPlace(String("five"), subject).Get());
      });
      Describe("and we call Remove(1)", [&]() {
        RemoveInPlace(String("one"), subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(String("zero"), subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(String("one"), subject));
        });
        It("Should return true when called with Contains(2)", [&]() {
          AssertTrue(Contains(String("two"), subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertTrue(Contains(String("three"), subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(String("four"), subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(String("five"), subject));
        });
        It("Should return nullptr when called with Get('zero')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject).Get());
        });
        It("Should return nullptr when called with Get('one')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("one"), subject).Get());
        });
        It("Should return 2 when called with Get('two')", [&]() {
          AssertEquals(2, GetInPlace(String("two"), subject).Get()[0]);
        });
        It("Should return 3 when called with Get('three')", [&]() {
          AssertEquals(3, GetInPlace(String("three"), subject).Get()[0]);
        });
        It("Should return 4 when called with Get('four')", [&]() {
          AssertEquals(4, GetInPlace(String("four"), subject).Get()[0]);
        });
        It("Should return nullptr when called with Get('five')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("five"), subject).Get());
        });
      });
      Describe("and we call Remove(2)", [&]() {
        RemoveInPlace(String("two"), subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(String("zero"), subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(String("one"), subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(String("two"), subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertTrue(Contains(String("three"), subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(String("four"), subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(String("five"), subject));
        });
        It("Should return nullptr when called with Get('zero')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject).Get());
        });
        It("Should return nullptr when called with Get('one')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("one"), subject).Get());
        });
        It("Should return nullptr when called with Get('two')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("two"), subject).Get());
        });
        It("Should return 3 when called with Get('three')", [&]() {
          AssertEquals(3, GetInPlace(String("three"), subject).Get()[0]);
        });
        It("Should return 4 when called with Get('four')", [&]() {
          AssertEquals(4, GetInPlace(String("four"), subject).Get()[0]);
        });
        It("Should return nullptr when called with Get('five')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("five"), subject).Get());
        });
      });
      Describe("and we call Remove(3)", [&]() {
        RemoveInPlace(String("three"), subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(String("zero"), subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(String("one"), subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(String("two"), subject));
        });
        It("Should return false when called with Contains(3)", [&]() {
          AssertFalse(Contains(String("three"), subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(String("four"), subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(String("five"), subject));
        });
        It("Should return nullptr when called with Get('zero')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject).Get());
        });
        It("Should return nullptr when called with Get('one')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("one"), subject).Get());
        });
        It("Should return nullptr when called with Get('two')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("two"), subject).Get());
        });
        It("Should return nullptr when called with Get('three')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("three"), subject).Get());
        });
        It("Should return 4 when called with Get('four')", [&]() {
          AssertEquals(4, GetInPlace(String("four"), subject).Get()[0]);
        });
        It("Should return nullptr when called with Get('five')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("five"), subject).Get());
        });
      });
      Describe("and we call Remove(4)", [&]() {
        RemoveInPlace(String("four"), subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(String("zero"), subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(String("one"), subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(String("two"), subject));
        });
        It("Should return false when called with Contains(3)", [&]() {
          AssertFalse(Contains(String("three"), subject));
        });
        It("Should return false when called with Contains(4)", [&]() {
          AssertFalse(Contains(String("four"), subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(String("five"), subject));
        });
        It("Should return nullptr when called with Get('zero')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("zero"), subject).Get());
        });
        It("Should return nullptr when called with Get('one')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("one"), subject).Get());
        });
        It("Should return nullptr when called with Get('two')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("two"), subject).Get());
        });
        It("Should return nullptr when called with Get('three')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("three"), subject).Get());
        });
        It("Should return nullptr when called with Get('four')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("four"), subject).Get());
        });
        It("Should return nullptr when called with Get('five')", [&]() {
          AssertEquals<int>(nullptr, GetInPlace(String("five"), subject).Get());
        });
      });
    });
  });
}

}