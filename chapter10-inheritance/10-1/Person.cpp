module person;

import std;

namespace HR {

Person::Person(std::string firstName, std::string lastName)
    : m_firstName{std::move(firstName)}, m_lastName{std::move(lastName)} {
  m_initials = extractInitials(m_firstName, m_lastName);
};

auto Person::getFirstName() const noexcept -> const std::string& {
  return m_firstName;
}

void Person::setFirstName(std::string firstName) {
  m_firstName = std::move(firstName);
  m_initials = extractInitials(m_firstName, m_lastName);
}

auto Person::getLastName() const noexcept -> const std::string& {
  return m_lastName;
}

void Person::setLastName(std::string lastName) {
  m_lastName = std::move(lastName);
  m_initials = extractInitials(m_firstName, m_lastName);
}

auto Person::getInitials() const noexcept -> const std::string& {
  return m_initials;
}

auto Person::extractFirstLetter(const std::string& name) noexcept -> char {
  return name.empty() ? '\0' : name[0];
}

auto Person::extractInitials(const std::string& firstName,
                             const std::string& lastName) -> std::string {
  return std::format("{}{}", extractFirstLetter(firstName),
                     extractFirstLetter(lastName));
}

Employee::Employee(std::string firstName, std::string lastName, unsigned id)
    : Person{firstName, lastName}, m_id{id} {}


}  // namespace HR
