#ifndef TRAITOROUS_BDD_H
#define TRAITOROUS_BDD_H

#include <cstdint>
#include <unistd.h>

#include "functions/types.h"

#include "cli/color.h"
#include "traits/unlawful/show.h"
#include "process/io.h"

#include "types/string.h"
#include "types/int32.h"

namespace traitorous {

uint32_t __traitorous_test_indent = 0;
uint32_t __traitorous_test_total  = 0;
uint32_t __traitorous_test_ran    = 0;
uint32_t __traitorous_test_pass   = 0;
uint32_t __traitorous_test_fail   = 0;
uint32_t __traitorous_test_skip   = 0;

LocalString Assert(bool result) noexcept {
  __traitorous_test_total++;
  __traitorous_test_ran++;
  if (result) {
    __traitorous_test_pass++;
    return Green("✔");
  } else {
    __traitorous_test_fail++;
    return Red("✖");
  }
}

LocalString SkippedTraitorousTest(const LocalString& str) {
  __traitorous_test_total++;
  __traitorous_test_skip++;
  return Yellow("?") + LocalString(" ") + str;
}

void PrintForTraitorousTest(const LocalString& str) {
  for (uint32_t i = 0; i < __traitorous_test_indent; i++) {
    Print(LocalString("  "));
  }
  PrintLn(str);
}

void Describe(const LocalString& str, std::function<void()> description) noexcept {
  PrintForTraitorousTest(str);
  __traitorous_test_indent++;
  description();
  __traitorous_test_indent--;
}

void It(const LocalString& str, Supplier<bool> assertion) noexcept {
  PrintForTraitorousTest(Assert(assertion()) + LocalString(" ") + str);
}

void It(const LocalString& str) noexcept {
  PrintForTraitorousTest(SkippedTraitorousTest(str));
}

int PrintFinalResultsForTraitorousTest() {
  if (__traitorous_test_fail == 0) {
    Print(Green("✔ "));
    Print(Green(Show(__traitorous_test_total)));
    Print(Green(" tests evaluated\n"));
  } else {
    Print(Red("✖ "));
    Print(Red(Show(__traitorous_test_total)));
    Print(Red(" tests evaluated\n"));
  }

  if (__traitorous_test_pass > 0) {
    Print(Green("  ✔ "));
    Print(Show(__traitorous_test_pass));
    Print(LocalString(" tests passed\n"));
  }

  if (__traitorous_test_fail > 0) {
    Print(Red("  ✖ "));
    Print(Show(__traitorous_test_fail));
    Print(LocalString(" tests failed\n"));
  }

  if(__traitorous_test_skip > 0) {
    Print(Yellow("  ? "));
    Print(Show(__traitorous_test_skip));
    Print(LocalString(" tests unimplemented\n"));
  }

  if (__traitorous_test_fail == 0) {
    return 0;
  } else {
    return 1;
  }
}

}

#endif
