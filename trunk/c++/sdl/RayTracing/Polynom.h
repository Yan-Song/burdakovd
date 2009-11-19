#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <algorithm>
#include "sdlapplication/Utils.h"

namespace RT
{
	class Polynom
	{
	private:
		std::vector<double> coefficients;

		friend const Polynom& operator /=(Polynom& a, const double b);
		friend Polynom operator /(const Polynom& a, const double b);
		friend const Polynom& operator *=(Polynom& a, const Polynom& b);
		friend Polynom operator *(const Polynom& a, const Polynom& b);
		friend const Polynom& operator -=(Polynom& a, const Polynom& b);
		friend const Polynom& operator +=(Polynom& a, const Polynom& b);
		friend Polynom operator -(const Polynom& a);
		friend Polynom operator -(const Polynom& a, const Polynom& b);
		friend Polynom operator +(const Polynom& a, const Polynom& b);

	public:
		Polynom(const double k, const unsigned int degree) : coefficients(degree + 1, 0)
		{
			coefficients[degree] = k;
		}

		Polynom(const double c = 0) : coefficients(1, c)
		{
		}

		// степень полинома (оценка сверху, так как старшие коэффициенты могут быть равны нулю)
		inline unsigned int Degree() const
		{
			return coefficients.size() - 1;
		}

		inline double GetCoefficient(const unsigned int degree) const
		{
			return degree <= Degree() ? coefficients[degree] : 0.0;
		}

		inline void SetCoefficient(const unsigned int degree, const double value)
		{
			assert(degree <= Degree());

			coefficients[degree] = value;
		}

		inline double Evaluate(const double value) const
		{
			double ans = 0;

			for(std::vector<double>::const_reverse_iterator it = coefficients.rbegin(); it != coefficients.rend(); ++it)
				ans = ans * value + *it;

			return ans;
		}

	};

	inline Polynom operator +(const Polynom& a, const Polynom& b)
	{
		const unsigned int an = a.Degree() + 1, bn = b.Degree() + 1;
		const unsigned int n = std::max(an, bn);

		Polynom ans(0, n - 1);
		
		for(unsigned int i = 0; i < n; ++i)
			ans.coefficients[i] = a.GetCoefficient(i) + b.GetCoefficient(i);
		
		return ans;
	}

	inline Polynom operator -(const Polynom& a, const Polynom& b)
	{
		const unsigned int an = a.Degree() + 1, bn = b.Degree() + 1;
		const unsigned int n = std::max(an, bn);

		Polynom ans(0, n - 1);
		
		for(unsigned int i = 0; i < n; ++i)
			ans.coefficients[i] = a.GetCoefficient(i) - b.GetCoefficient(i);
		
		return ans;
	}

	inline Polynom operator -(const Polynom& a)
	{
		const unsigned int n = a.Degree() + 1;

		Polynom ans(0, n - 1);
		
		for(unsigned int i = 0; i < n; ++i)
			ans.coefficients[i] = -a.coefficients[i];

		return ans;
	}

	inline const Polynom& operator +=(Polynom& a, const Polynom& b)
	{
		return a = a + b;
	}

	inline const Polynom& operator -=(Polynom& a, const Polynom& b)
	{
		return a = a - b;
	}

	inline Polynom operator *(const Polynom& a, const Polynom& b)
	{
		const unsigned int an = a.Degree() + 1, bn = b.Degree() + 1;
		const unsigned int degree = a.Degree() + b.Degree();

		Polynom ans(0, degree);

		for(unsigned int i = 0; i < an; ++i)
			for(unsigned int j = 0; j < bn; ++j)
				ans.coefficients[i + j] += a.coefficients[i] * b.coefficients[j];

		return ans;
	}

	inline const Polynom& operator *=(Polynom& a, const Polynom& b)
	{
		return a = a * b;
	}

	inline Polynom operator /(const Polynom& a, const double b)
	{
		const unsigned int n = a.Degree() + 1;

		Polynom ans(0, n - 1);

		for(unsigned int i = 0; i < n; ++i)
			ans.coefficients[i] = a.coefficients[i] / b;

		return ans;
	}

	inline const Polynom& operator /=(Polynom& a, const double b)
	{
		return a = a / b;
	}
}

#endif
