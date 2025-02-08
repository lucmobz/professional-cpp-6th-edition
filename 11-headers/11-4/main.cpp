import simulator;

auto main() -> int {
  using namespace simulator;

  CarSimulator carSimulator;
  BikeSimulator bikeSimulator;

  carSimulator.setOdometer(42.0);
  bikeSimulator.setOdometer(42.0);

  //convertMilesToKm(42.0); // ERROR: Does not compile
}