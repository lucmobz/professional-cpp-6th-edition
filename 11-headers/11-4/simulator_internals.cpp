module simulator:internals;

// Interestingly this is in a TU file and does not need static/anonymous
// namespace (which would give internal linkage and make this unavailable from
// other TUs)
double convertMilesToKm(double distanceMiles) {
  constexpr auto KM_PER_MILE{1.6};
  return distanceMiles * KM_PER_MILE;
}
