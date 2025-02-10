import raii;
import std;

auto main() -> int {
  using namespace raii;

  Pointer<int> ptr0;
  Pointer<int> ptr1{new int{42}};
  auto ptr2{std::move(ptr1)};

  ptr0 = std::move(ptr2);

  std::println("{}", *ptr0);
  std::println("{}", *std::as_const(ptr0));

  // These should not compile if the constructor is made explicit (no implicit
  // conversions)

  // ptr2 = new int{-1};
  // ptr0 = ptr2.release();

  // ERROR: this is undefined behaviour, is there a way to fix it?
  // Pointer<int> ptr4{new int[42]{}};
  // std::unique_ptr<int> uptr{new int[42]};
  // This is correct and calls delete[]
  // std::unique_ptr<int[]> uptr{new int[42]};

  ptr0.reset(new int{1001});
  ptr0 = std::move(ptr0);
  ptr0.reset();
}
