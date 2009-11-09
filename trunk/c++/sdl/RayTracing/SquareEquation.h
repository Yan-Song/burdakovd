#ifndef SQUAREEQUATION_H
#define SQUAREEQUATION_H

#include "Polynom.h"
#include <stdexcept>
#include <map>
#include "sdlapplication/Utils.h"
#include <cmath>

namespace RT
{
	// �������, �������� ��������� ������ � ������ �������
	// ������� std::invalid_argument ���� ��� ������
	inline std::pair<double, double> SolveSquareEquation(const Polynom& p)
	{
		assert(p.Degree() <= 2);
		assert(p.Degree() > 0);

		const double a = p.GetCoefficient(2);
		const double b = p.GetCoefficient(1);
		const double c = p.GetCoefficient(0);

		if(a == 0)
		{
			// �������� bx + c = 0
			if(b == 0)
				throw new std::invalid_argument("");
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
				throw new std::exception("");

			const double x1 = (- b + sqrt(D)) / 2 / a;
			const double x2 = (- b - sqrt(D)) / 2 / a;

			return std::pair<double, double>(x1, x2);
		}
	}
};

#endif