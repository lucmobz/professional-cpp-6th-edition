export module person;

import std;

export class Person {
 public:
  // These functions cannot be defaulted here because they would require the
  // complete type Impl
  Person();
  explicit Person(std::string firstName, std::string lastName);
  Person(const Person& other);
  Person(Person&& other);

  ~Person();

  Person& operator=(const Person& other);
  Person& operator=(Person&& other);

  [[nodiscard]] auto getFirstName() const noexcept -> const std::string&;
  void setFirstName(std::string firstName);

  [[nodiscard]] auto getLastName() const noexcept -> const std::string&;
  void setLastName(std::string lastName);

  [[nodiscard]] auto getInitials() const noexcept -> const std::string&;

 private:
  class Impl;

  // Using an in-class initializer forces the compiler to require the complete
  // type Impl. A rare case where this is better left uninitialized in the class
  std::unique_ptr<Impl> m_impl;
};