module person;

import std;

class Person::Impl {
  // No reason to have anything private as this entire class is not
  // accessible
 public:
  Impl() = default;

  explicit Impl(std::string firstName, std::string lastName)
      : m_firstName{std::move(firstName)},
        m_lastName{std::move(lastName)},
        m_initials{extractInitials(m_firstName, m_lastName)} {};

  [[nodiscard]] auto getFirstName() const noexcept -> const std::string& {
    return m_firstName;
  }

  void setFirstName(std::string firstName) {
    m_firstName = std::move(firstName);
    m_initials = extractInitials(m_firstName, m_lastName);
  }

  [[nodiscard]] auto getLastName() const noexcept -> const std::string& {
    return m_lastName;
  }

  void setLastName(std::string lastName) {
    m_lastName = std::move(lastName);
    m_initials = extractInitials(m_firstName, m_lastName);
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

Person::Person() : m_impl{std::make_unique<Impl>()} {};

Person::Person(std::string firstName, std::string lastName)
    : m_impl{
          std::make_unique<Impl>(std::move(firstName), std::move(lastName))} {}

Person::Person(const Person& other)
    : m_impl{std::make_unique<Impl>(*other.m_impl)} {}

Person::Person(Person&&) = default;

Person::~Person() = default;

Person& Person::operator=(const Person& other) {
  if (this == &other) return *this;
  *m_impl = *other.m_impl;
  return *this;
};

Person& Person::operator=(Person&&) = default;

auto Person::getFirstName() const noexcept -> const std::string& {
  return m_impl->getFirstName();
}

void Person::setFirstName(std::string firstName) {
  m_impl->setFirstName(std::move(firstName));
}

auto Person::getLastName() const noexcept -> const std::string& {
  return m_impl->getLastName();
}

void Person::setLastName(std::string lastName) {
  m_impl->setLastName(std::move(lastName));
}

auto Person::getInitials() const noexcept -> const std::string& {
  return m_impl->getInitials();
}
