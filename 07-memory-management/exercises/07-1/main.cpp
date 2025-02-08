import std;

auto main() -> int {
  const size_t numberOfElements{10};
  int* values{new int[numberOfElements]};

  // Set values to their index value.
  for (int index{0}; index < numberOfElements; ++index) {
    values[index] = index;
  }

  // Set last value to 99.
  values[10] = 99;  // <--- Runtime error: out-of-range

  // Print all values.
  for (int index{0}; index <= numberOfElements; ++index) {
    std::print("{} ", values[index]);  // <--- Runtime error: out-of-range
  }

  // <--- Missing delete[]
  delete[] values;
}