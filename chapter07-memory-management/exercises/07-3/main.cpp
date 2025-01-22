import std;

class Point {
 public:
  Point(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z} {}

  const auto& getX() const { return m_x; }
  const auto& getY() const { return m_y; }
  const auto& getZ() const { return m_z; }

 private:
  double m_x{0.0};
  double m_y{0.0};
  double m_z{0.0};
};

void printPoint(const Point& point) {
  std::print("{}, {}, {}", point.getX(), point.getY(), point.getZ());
}

auto main() -> int {
  auto point{std::make_unique<Point>(1.0, 2.0, 3.0)};
  printPoint(*point);
}