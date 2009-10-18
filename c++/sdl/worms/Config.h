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
};

#endif
