export module person;

import std;

export class Person {
 public:
  Person() = default;

  // Order of initialization matters here, as in this version there is the
  // initials invariant that needs to be mantained
  explicit Person(std::string firstName, std::string lastName)
      : m_firstName{std::move(firstName)},
        m_lastName{std::move(lastName)},
        m_initials{extractInitials(m_firstName, m_lastName)} {
          // As a more safe option put dependent initializations here
        };

  // Skipping initials as they are maintained as an invariant
  bool operator==(const Person& other) const noexcept {
    return m_firstName == other.m_firstName && m_lastName == other.m_lastName;
  }

  bool operator!=(const Person& other) const noexcept {
    return !(*this == other);
  }

  bool operator<(const Person& other) const noexcept {
    if (m_firstName < other.m_firstName) return true;
    if (m_firstName == other.m_firstName && m_lastName < other.m_lastName)
      return true;
    return false;
  }

  bool operator<=(const Person& other) const noexcept {
    return *this < other || *this == other;
  }

  bool operator>(const Person& other) const noexcept {
    return !(*this <= other);
  }

  bool operator>=(const Person& other) const noexcept {
    return !(*this < other);
  }

  [[nodiscard]] auto getFirstName() const noexcept -> const std::string& {
    return m_firstName;
  }

  Person& setFirstName(std::string firstName) {
    m_firstName = std::move(firstName);
    m_initials = extractInitials(m_firstName, m_lastName);
    return *this;
  }

  [[nodiscard]] auto getLastName() const noexcept -> const std::string& {
    return m_lastName;
  }

  Person& setLastName(std::string lastName) {
    m_lastName = std::move(lastName);
    m_initials = extractInitials(m_firstName, m_lastName);
    return *this;
  }

  [[nodiscard]] auto getInitials() const noexcept -> const std::string& {
    return m_initials;
  }

 private:
  static auto extractFirstLetter(const std::string& name) noexcept -> char {
    if (name.empty()) return '\0';
    return name[0];
  }

  static auto extractInitials(const std::string& firstName,
                              const std::string& lastName) -> std::string {
    return std::format("{}{}", extractFirstLetter(firstName),
                       extractFirstLetter(lastName));
  }

  std::string m_firstName{};
  std::string m_lastName{};
  std::string m_initials{};
};