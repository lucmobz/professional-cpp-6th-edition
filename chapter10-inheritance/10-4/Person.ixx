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

  virtual auto toString() const -> std::string;

 protected:
  Person() = default;

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

  auto getId() const noexcept;

  auto toString() const -> std::string override;

 protected:
  Employee() = default;

 private:
  unsigned m_id{0};
};

class Manager : public virtual Employee {
 public:
  using Employee::Employee;

  auto toString() const -> std::string override;

 protected:
  Manager() = default;
};

class Director : public virtual Employee {
 public:
  using Employee::Employee;

  auto toString() const -> std::string override;

 protected:
  Director() = default;
};

class DirectorManager : public Director, public Manager {
 public:
  using Director::Director;
  DirectorManager(std::string firstName, std::string lastName, unsigned id)
      : Employee{firstName, lastName, id}, Director{}, Manager{} {}

  auto toString() const -> std::string override;
};


}  // namespace HR