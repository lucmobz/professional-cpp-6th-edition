import std;

int foo(int arr[2]) { return arr[0] + arr[1]; }

auto main() -> int {
  std::println("hello");
  std::println("world");
  int arr[3];
  return foo(arr);
}