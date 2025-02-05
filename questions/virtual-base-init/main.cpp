import zoo;
import std;

auto main() -> int {
  std::vector<std::unique_ptr<Animal>> animals;

  animals.push_back(std::make_unique<Zebra>(400.0, 42));
  animals.push_back(std::make_unique<Lion>(200.0, 3));
  animals.push_back(std::make_unique<LionZebra>(300.0, 0, 10));

  for (auto& animal : animals) animal->identify();
}
