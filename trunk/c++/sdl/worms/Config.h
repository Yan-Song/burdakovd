#ifndef CONFIG_H
#define CONFIG_H

#include <Color.h>

// здесь указан список различных параметров
struct Config
{
	// в секундах
	static const double MovementTime;
	static const double DiscoverTime;
	// количество энергии, которую червь хранит в одной своей ячейке
	static const double WormEnergyPerCell;
	// количество энергии, которую содержит одня ячейка еды
	static const double FoodEnergyPerCell;
	// затраты энергии червем за одну секунду
	static const double EnergyLossPerSecond;
	// количество энергии ниже которого червь иметь не может, умрёт
	static const double DeathEnergyLevel;
	// количество энергии, при котором червь начинает делиться
	static const double ReplicateEnergyLevel;
	// радиус трупа
	static const int CorpseRadius;

	// сколько еды изначально
	static const int InitialFoodCount;

	// сколько появляется каждую секунду
	static const double FoodPerSecond;

	// размер ячейки поля ва пикселях
	static const int CellSize;
	// размеры поля в ячейках
	static const int FieldWidth, FieldHeight;

	static const double StartEnergy;

	static const Color GraphBackground;
	static const double GraphUpdateFrequency;
	static const int GraphStep;

	static const double GodEnergyDelta;
};

#endif
