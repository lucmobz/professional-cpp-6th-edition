export module simulator:bike;

import std;

export namespace simulator {

class BikeSimulator {
 public:
  BikeSimulator();
};

}  // namespace simulator

// Implementation
using namespace simulator;

BikeSimulator::BikeSimulator() { std::println(__func__); }
