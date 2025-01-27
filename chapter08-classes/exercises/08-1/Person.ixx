export module person;

import std;

export class Person {
 public:
  Person(std::string_view firstName, std::string_view lastName)
      : m_firstName{firstName}, m_lastName{lastName} {}

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