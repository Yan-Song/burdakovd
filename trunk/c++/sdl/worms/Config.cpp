#include "Config.h"

// параметры

const double Config::MovementTime = 0.03;
const double Config::DiscoverTime = 0.001;
const double Config::WormEnergyPerCell = 10.0;
const double Config::FoodEnergyPerCell = 1.0;
const double Config::EnergyLossPerSecond = 1;
const double Config::DeathEnergyLevel = Config::WormEnergyPerCell; // умирает, когда остаетс€ меньше одной €чейки
const double Config::ReplicateEnergyLevel = 200.0;
