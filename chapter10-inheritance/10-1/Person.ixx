export module person;

import std;

export namespace HR {

class Person {
 public:
  explicit Person(std::string firstName, std::string lastName);
  Person(const Person&) = default;
  Person(Person&&) = default;

  virtual ~Person() = default;

  Person& operator=(const Person&) = default;
  Person& operator=(Person&&) = default;

  auto operator<=>(const Person&) const noexcept = default;

  auto getFirstName() const noexcept -> const std::string&;
  void setFirstName(std::string firstName);

  auto getLastName() const noexcept -> const std::string&;
  void setLastName(std::string lastName);

  auto getInitials() const noexcept -> const std::string&;

 private:
  static auto extractFirstLetter(const std::string& name) noexcept -> char;

  static auto extractInitials(const std::string& firstName,
                              const std::string& lastName) -> std::string;

  std::string m_firstName{};
  std::string m_lastName{};
  std::string m_initials{};
};

class Employee : public Person {
 public:
  Employee(std::string firstName, std::string lastName, unsigned id);

  Employee(const Employee&) = default;
  Employee(Employee&&) = default;

  virtual ~Employee() override = default;

  Employee& operator=(const Employee&) = default;
  Employee& operator=(Employee&&) = default;

  constexpr auto getId() const noexcept;

 private:
  unsigned m_id{0};
};

class Manager : public Employee {
 public:
  using Employee::Employee;
};

class Director : public Employee {
 public:
  using Employee::Employee;
};

constexpr auto Employee::getId() const noexcept { return m_id; }

}  // namespace HR