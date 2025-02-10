export module raii;

import std;

export namespace raii {

template <typename ValueType>
class Pointer {
  using PointerType = ValueType*;

  static_assert(!std::is_array_v<ValueType>);

 public:
  Pointer() = default;
  // No discard allowed becuase it would enable acquiring a resource through a
  // temporary and then immediately releasing it
  [[nodiscard]] explicit Pointer(PointerType rawPointer);
  Pointer(const Pointer&) = delete;
  Pointer(Pointer&& other) noexcept;

  ~Pointer();

  auto operator=(const Pointer&) -> Pointer& = delete;
  auto operator=(Pointer&& other) noexcept -> Pointer&;

  auto operator*() -> ValueType&;
  auto operator*() const -> const ValueType&;

  void swap(Pointer& other) noexcept;

  void reset(PointerType rawPointer = nullptr);

  // No discard allowed because it would mean leaking the resource
  [[nodiscard]] auto release() -> PointerType;

  template <std::convertible_to<ValueType> AssignType>
  void assign(const AssignType& value);

  friend void swap(Pointer& first, Pointer& second) noexcept;

 private:
  PointerType m_rawPointer{nullptr};
};

template <typename ValueType>
Pointer<ValueType>::Pointer(PointerType rawPointer) : m_rawPointer{rawPointer} {
  if (!m_rawPointer)
    throw std::runtime_error{"nullptr was passed in the constructor"};
}

template <typename ValueType>
Pointer<ValueType>::Pointer(Pointer&& other) noexcept {
  swap(other);
}

template <typename ValueType>
auto Pointer<ValueType>::operator=(Pointer&& other) noexcept -> Pointer& {
  auto tmp{std::move(other)};
  swap(tmp);
  return *this;
}

template <typename ValueType>
auto Pointer<ValueType>::operator*() -> ValueType& {
  // Using Scott Meyers' const_cast pattern
  return const_cast<ValueType&>(*std::as_const(*this));
}

template <typename ValueType>
auto Pointer<ValueType>::operator*() const -> const ValueType& {
  return *m_rawPointer;
}

template <typename ValueType>
Pointer<ValueType>::~Pointer() {
  reset();
}

template <typename ValueType>
void Pointer<ValueType>::swap(Pointer& other) noexcept {
  std::swap(m_rawPointer, other.m_rawPointer);
}

template <typename ValueType>
void Pointer<ValueType>::reset(PointerType rawPointer) {
  // Deleting a nullptr does nothing;
  delete m_rawPointer;
  m_rawPointer = rawPointer;
}

template <typename ValueType>
auto Pointer<ValueType>::release() -> PointerType {
  return std::exchange(m_rawPointer, nullptr);
}

template <typename ValueType>
void swap(Pointer<ValueType>& first, Pointer<ValueType>& second) noexcept {
  first.swap(second);
}

template <typename ValueType>
template <std::convertible_to<ValueType> AssignType>
void Pointer<ValueType>::assign(const AssignType& value) {
  if (!m_rawPointer) throw std::runtime_error{"Trying to assign to a nullptr"};
  *m_rawPointer = value;
}

}  // namespace raii
