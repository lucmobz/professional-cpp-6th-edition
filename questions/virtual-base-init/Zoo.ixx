// * Question: what happens to constructors in a diamond inheritance hierarchy
// when both immediate base classes have the second base as virtual?
export module zoo;

import std;

export class Animal {
 public:
  Animal(double weight) noexcept : m_weight{weight} {}

  virtual ~Animal() = default;

  virtual void identify() const = 0;

  [[nodiscard]] constexpr auto getWeight() const noexcept -> double {
    return m_weight;
  }

 protected:
  Animal() = default;

 private:
  double m_weight{0.0};
};

export class Zebra : public virtual Animal {
 public:
  Zebra(double weight, unsigned numStripes) noexcept
      : Animal{weight + 20}, m_numStripes{numStripes} {}

  void identify() const override {
    std::println("Zebra: {} stripes, {} kilos", m_numStripes, getWeight());
  }

  [[nodiscard]] constexpr auto getNumStripes() const noexcept {
    return m_numStripes;
  }

 private:
  unsigned m_numStripes{0};
};

export class Lion : public virtual Animal {
 public:
  Lion(double weight, unsigned zebrasEaten) noexcept
      : Animal{weight - 80}, m_zebrasEaten{zebrasEaten} {}

  void identify() const override {
    std::println("Lion: {} zebras eaten, {} kilos", m_zebrasEaten,
                 getWeight());
  }

  [[nodiscard]] constexpr auto getZebraEaten() const noexcept {
    return m_zebrasEaten;
  }

 protected:
  Lion(unsigned zebrasEaten) : m_zebrasEaten{zebrasEaten} {}

 private:
  unsigned m_zebrasEaten{0};
};

export class LionZebra : public Lion, public Zebra {
 public:
  LionZebra(double weight, unsigned zebrasEaten, unsigned numStripes)
      : Lion{zebrasEaten}, Zebra{weight, numStripes} {}

  void identify() const override {
    std::println("Not sure..., {} kilos", getWeight());
  }
};

// * Answer: the second base constructors invoked by the immediate base classes
// are ignored, it is the responsibility of the most derived class to initialize
// the virtual base class (of which there is a single sub-object). If one base
// class is not virtual it will still have duplicate objects. Normally derived
// classes do not have access to  second base classes constructors
