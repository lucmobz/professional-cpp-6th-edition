export module person;

import std;

export class Person {
 public:
  Person() = default;

  explicit(true) Person(std::string_view firstName, std::string_view lastName)
      : Person(firstName, lastName, firstName.empty() ? '\0' : firstName[0],
               lastName.empty() ? '\0' : lastName[0]){};

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

  [[nodiscard]] auto getFirstNameInitial() const -> char {
    return m_firstNameInitial;
  }

  [[nodiscard]] auto getLastNameInitial() const -> char {
    return m_lastNameInitial;
  }

 private:
  // Helper constructor made private becuase it does not make sense to have a
  // mismatch between the name and initials
  Person(std::string_view firstName, std::string_view lastName,
         char firstNameInitial, char lastNameInitial)
      : m_firstName{firstName},
        m_lastName{lastName},
        m_firstNameInitial{firstNameInitial},
        m_lastNameInitial{lastNameInitial} {}

  std::string m_firstName{};
  std::string m_lastName{};
  // Solution uses std::format to merge the two letters into a single initials'
  // std::string
  char m_firstNameInitial{};
  char m_lastNameInitial{};
};