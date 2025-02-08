export module person;

import std;

export class Person {
 public:
  Person() { std::println(__func__); }

  Person(const Person& other)
      : m_firstName{other.m_firstName}, m_lastName{other.m_lastName} {
    std::println("Person(const Person&)");
  }

  explicit(true) Person(std::string_view firstName, std::string_view lastName)
      : m_firstName{firstName}, m_lastName{lastName} {
    std::println("Person(std::string_view, std::string_view)");
  }

  ~Person() { std::println(__func__); }

  Person& operator=(const Person& rhs) {
    if (this == &rhs) return *this;

    m_firstName = rhs.m_lastName;
    m_lastName = rhs.m_lastName;

    std::println("Person& operator=(const Person&)");
  }

  [[nodiscard]] auto getFirstName() const -> const std::string& {
    return m_firstName;
  }

  Person& setFirstName(std::string_view firstName) {
    m_firstName = firstName;
    return *this;
  }

  [[nodiscard]] auto getLastName() const -> const std::string& {
    return m_lastName;
  }

  Person& setLastName(std::string_view lastName) {
    m_lastName = lastName;
    return *this;
  }

 private:
  std::string m_firstName;
  std::string m_lastName;
};