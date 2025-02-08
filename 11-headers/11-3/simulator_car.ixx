export module simulator:car;

import std;

export namespace simulator {

class CarSimulator {
 public:
  CarSimulator();
};

}  // namespace simulator

// Implementation
using namespace simulator;

CarSimulator::CarSimulator() { std::println(__func__); }
