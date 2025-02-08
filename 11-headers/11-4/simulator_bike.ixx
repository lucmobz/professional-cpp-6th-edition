export module simulator:bike;

import std;
import :internals;

export namespace simulator {

class BikeSimulator {
 public:
  BikeSimulator();

  void setOdometer(double distanceMiles) const;
};

}  // namespace simulator

// Implementation
namespace simulator {

BikeSimulator::BikeSimulator() { std::println(__func__); }

void BikeSimulator::setOdometer(double distanceMiles) const {
  const auto distanceKm{convertMilesToKm(distanceMiles)};
  std::println("Bike odometer: {}km", distanceKm);
}

}  // namespace simulator
