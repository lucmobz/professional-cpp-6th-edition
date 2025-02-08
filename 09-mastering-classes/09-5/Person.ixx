export module person;

import std;

export class Person {
 public:
  Person() = default;

  explicit Person(std::string firstName, std::string lastName);

  [[nodiscard]] auto operator<=>(const Person&) const noexcept = default;

  [[nodiscard]] auto getFirstName() const& noexcept -> const std::string&;
  [[nodiscard]] auto getFirstName() && noexcept -> std::string&&;
  auto setFirstName(std::string firstName) -> Person&;

  [[nodiscard]] auto getLastName() const& noexcept -> const std::string&;
  [[nodiscard]] auto getLastName() && noexcept -> std::string&&;
  auto setLastName(std::string lastName) -> Person&;

  [[nodiscard]] auto getInitials() const& noexcept -> const std::string&;
  [[nodiscard]] auto getInitials() && noexcept -> std::string&&;

 private:
  static auto extractInitials(const std::string& firstName,
                              const std::string& lastName) -> std::string;

  std::string m_firstName{};
  std::string m_lastName{};
  std::string m_initials{};
};

inline Person::Person(std::string firstName, std::string lastName)
    : m_firstName{std::move(firstName)}, m_lastName{std::move(lastName)} {
  // This is done here to protect against class members rearrangement
  m_initials = extractInitials(m_firstName, m_lastName);
};

inline auto Person::getFirstName() const& noexcept -> const std::string& {
  return m_firstName;
}

inline auto Person::getFirstName() && noexcept -> std::string&& {
  return std::move(m_firstName);
}

inline Person& Person::setFirstName(std::string firstName) {
  m_firstName = std::move(firstName);
  m_initials = extractInitials(m_firstName, m_lastName);
  return *this;
}

inline auto Person::getLastName() const& noexcept -> const std::string& {
  return m_lastName;
}

inline auto Person::getLastName() && noexcept -> std::string&& {
  return std::move(m_lastName);
}

inline Person& Person::setLastName(std::string lastName) {
  m_lastName = std::move(lastName);
  m_initials = extractInitials(m_firstName, m_lastName);
  return *this;
}

inline auto Person::getInitials() const& noexcept -> const std::string& {
  return m_initials;
}

auto Person::getInitials() && noexcept -> std::string&& {
  return std::move(m_initials);
}

inline auto Person::extractInitials(
    const std::string& firstName, const std::string& lastName) -> std::string {
  auto firstLetter{firstName.empty() ? '\0' : firstName[0]};
  auto lastLetter{lastName.empty() ? '\0' : lastName[0]};
  return std::format("{}{}", firstLetter, lastLetter);
}
