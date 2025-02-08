#define IDENTIFIER 1

#if (IDENTIFIER == 1)
#ifdef _MSC_VER
// There is no #warning preprocessor directive in MSVC
#else
#warning "You have been warned (by some compiler)"
#endif
#elif (IDENTIFIER == 0)
#else
#error "You shall not pass"
#endif

#undef IDENTIFIER

import std;

auto main() -> int { std::println("Hello Preprocessor"); }
