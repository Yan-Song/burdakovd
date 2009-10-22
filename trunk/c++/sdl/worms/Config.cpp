#include "Config.h"

// параметры

const double Config::MovementTime = 0.05;
const double Config::DiscoverTime = 0.001;
const double Config::WormEnergyPerCell = 10.0;
const double Config::FoodEnergyPerCell = 1;
const double Config::EnergyLossPerSecond = 1;
const double Config::DeathEnergyLevel = Config::WormEnergyPerCell; // умирает, когда остается меньше одной ячейки
const double Config::ReplicateEnergyLevel = 200.0;
const int Config::CorpseRadius = 3;
