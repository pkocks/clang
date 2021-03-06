// RUN: %clang_cc1 -std=c++1y -fblocks -fsyntax-only -verify %s
// PR16946
// expected-no-diagnostics

auto foo() {
  static_assert(sizeof(__func__) == 4, "foo");
  static_assert(sizeof(__FUNCTION__) == 4, "foo");
  static_assert(sizeof(__PRETTY_FUNCTION__) == 11, "auto foo()");
  return 0;
}

auto bar() -> decltype(42) {
  static_assert(sizeof(__func__) == 4, "bar");
  static_assert(sizeof(__FUNCTION__) == 4, "bar");
  static_assert(sizeof(__PRETTY_FUNCTION__) == 10, "int bar()");
  return 0;
}

int main() {
  static_assert(sizeof(__func__) == 5, "main");
  static_assert(sizeof(__FUNCTION__) == 5, "main");
  static_assert(sizeof(__PRETTY_FUNCTION__) == 11, "int main()");

  []() {
    static_assert(sizeof(__func__) == 11, "operator()");
    static_assert(sizeof(__FUNCTION__) == 11, "operator()");
    static_assert(sizeof(__PRETTY_FUNCTION__) == 51,
                  "auto main()::<anonymous class>::operator()() const");
    return 0;
  }
  ();

  ^{
    // FIXME: This is obviously wrong.
    static_assert(sizeof(__func__) == 1, "__main_block_invoke");
    static_assert(sizeof(__FUNCTION__) == 1, "__main_block_invoke");
    static_assert(sizeof(__PRETTY_FUNCTION__) == 1, "__main_block_invoke");
  }
  ();
}
