#include "Config.h"

// параметры

const double Config::MovementTime = 0.1;
const double Config::DiscoverTime = 0.01;
const double Config::WormEnergyPerCell = 10.0;
const double Config::FoodEnergyPerCell = 1;
const double Config::EnergyLossPerSecond = 1;
const double Config::DeathEnergyLevel = 2 * Config::WormEnergyPerCell; // умирает, когда остается меньше одной ячейки
const double Config::ReplicateEnergyLevel = 200.0;
const int Config::CorpseRadius = 2;
const int Config::InitialFoodCount = 10;
const double Config::FoodPerSecond = 2;
const double Config::StartEnergy = 100;

const int Config::CellSize = 10;
const int Config::FieldHeight = 40;
const int Config::FieldWidth = 60;

const Color Config::GraphBackground(Palette::White);
const Color Config::GraphLines(Color(0xd0d0ff));
const double Config::GraphUpdateFrequency = 0.1;
const int Config::GraphStep = 10;
const double Config::GodEnergyDelta = 100;
