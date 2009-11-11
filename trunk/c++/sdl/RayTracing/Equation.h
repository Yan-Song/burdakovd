#ifndef SQUAREEQUATION_H
#define SQUAREEQUATION_H

#include "Polynom.h"
#include <stdexcept>
#include <map>
#include "sdlapplication/Utils.h"
#include <cmath>

namespace RT
{
	// функция, решающая уравнения первой и второй степени
	// бросает std::invalid_argument если нет корней
	inline std::pair<double, double> SolveSquareEquation(const Polynom& p)
	{
		assert(p.Degree() <= 2);
		assert(p.Degree() > 0);

		const double a = p.GetCoefficient(2);
		const double b = p.GetCoefficient(1);
		const double c = p.GetCoefficient(0);

		if(a == 0)
		{
			// Линейное bx + c = 0
			if(b == 0)
				throw std::invalid_argument("");
			else
			{
				const double x = - c / b;
				return std::pair<double, double>(x, x);
			}
		}
		else
		{
			const double D = sqr(b) - 4 * a * c;

			if(D < 0)
				throw std::invalid_argument("");

			const double x1 = (- b + sqrt(D)) / 2 / a;
			const double x2 = (- b - sqrt(D)) / 2 / a;

			return std::pair<double, double>(x1, x2);
		}
	}

	// ax + b = 0
	inline double SolveLinearEquation(const Polynom& p)
	{
		assert(p.Degree() == 1);

		const double a = p.GetCoefficient(1);
		const double b = p.GetCoefficient(0);

		if(a == 0)
			throw std::invalid_argument("");
		else
			return - b / a;
	}
};

#endif