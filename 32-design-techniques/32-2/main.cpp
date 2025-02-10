import raii;
import std;

auto main() -> int {
  using namespace raii;

  try {
    Pointer<int> ptr0{new int{42}};
    Pointer<int> ptr1{nullptr}; // Triggers an exception
  } catch (const std::exception& e) {
    std::println(std::cerr, "{}", e.what());
  }
}
