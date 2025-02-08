export module simulator:car;

import std;
import :internals;

export namespace simulator {

class CarSimulator {
 public:
  CarSimulator();

  void setOdometer(double distanceMiles) const;
};

}  // namespace simulator

// Implementation
namespace simulator {

CarSimulator::CarSimulator() { std::println(__func__); }

void CarSimulator::setOdometer(double distanceMiles) const {
  const auto distanceKm{convertMilesToKm(distanceMiles)};
  std::println("Car odometer: {}km", distanceKm);
}

}  // namespace simulator
