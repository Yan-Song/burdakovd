#ifndef CONFIG_H
#define CONFIG_H

// здесь указан список различных параметров
struct Config
{
	// в секундах
	static const double MovementTime;
	static const double DiscoverTime;
	// количество энергии, которую червь хранит в одной своей €чейке
	static const double WormEnergyPerCell;
	// количество энергии, которую содержит одн€ €чейка еды
	static const double FoodEnergyPerCell;
	// затраты энергии червем за одну секунду
	static const double EnergyLossPerSecond;
	// количество энергии ниже которого червь иметь не может, умрЄт
	static const double DeathEnergyLevel;
	// количество энергии, при котором червь начинает делитьс€
	static const double ReplicateEnergyLevel;
};

#endif
