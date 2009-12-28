#ifndef BATTLESETTINGS_H
#define BATTLESETTINGS_H

#include <vector>
#include <Color.h>

struct Team
{
	size_t ID;

	Color color;

	size_t Count;

	Team(const size_t ID_, const Color& color_, const size_t Count_) : ID(ID_), color(color_), Count(Count_)
	{
	}
};

typedef std::vector<Team> Teams;

#endif
