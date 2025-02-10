import raii;
import std;

auto main() -> int {
  using namespace raii;

  try {
    Pointer<int> ptr{new int{0}};
    ptr.assign(1);
    std::println("{}", *ptr);

    ptr.reset();
    ptr.assign(42);
  } catch (const std::exception& e) {
    std::println(std::cerr, "{}", e.what());
  }
}
