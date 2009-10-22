#ifndef CONFIG_H
#define CONFIG_H

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
};

#endif
