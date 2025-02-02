export module person;

import std;

export class Person {
 public:
  Person() = default;

  // If a std::string is moved as argument then there will be two moves only,
  // while if a std::string_view was used, there would be a construct from a
  // std::string_view. This is the optimal way in all cases for all arguments
  // (c-string literal, lvalue std::string, rvalue std::string) since a copy is
  // actually needed. std::string_view is blind to potential std::move of the
  // arguments
  explicit Person(std::string firstName, std::string lastName)
      : m_firstName{std::move(firstName)}, m_lastName{std::move(lastName)} {}

  Person(const Person& other) : Person{other.m_firstName, other.m_lastName} {}

  Person(Person&& other) noexcept {
    // No message printing because that is not noexcept
    swap(other);
  }

  ~Person() = default;

  Person& operator=(const Person& other) {
    auto tmp{other};
    swap(tmp);
    return *this;
  }

  Person& operator=(Person&& other) noexcept {
    // No message printing because that is not noexcept
    auto tmp{std::move(other)};
    swap(tmp);
    return *this;
  }

  void swap(Person& other) noexcept {
    std::swap(m_firstName, other.m_firstName);
    std::swap(m_lastName, other.m_lastName);
  }

  [[nodiscard]] auto getFirstName() const noexcept -> const std::string& {
    return m_firstName;
  }

  Person& setFirstName(std::string firstName) {
    m_firstName = std::move(firstName);
    return *this;
  }

  [[nodiscard]] auto getLastName() const noexcept -> const std::string& {
    return m_lastName;
  }

  Person& setLastName(std::string lastName) {
    m_lastName = std::move(lastName);
    return *this;
  }

  friend void swap(Person& first, Person& second) noexcept {
    first.swap(second);
  }

 private:
  std::string m_firstName{};
  std::string m_lastName{};
};
