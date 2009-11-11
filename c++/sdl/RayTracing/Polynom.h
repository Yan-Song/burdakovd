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
		Polynom(const double k, const int degree)
		{
			assert(degree >= 0);
			coefficients.resize(degree + 1);
			coefficients[degree] = k;
		}

		Polynom(const double c = 0)
		{
			coefficients.resize(1);
			coefficients[0] = c;
		}

		// степень полинома (оценка сверху, так как старшие коэффициенты могут быть равны нулю)
		inline int Degree() const
		{
			return coefficients.size() - 1;
		}

		inline double GetCoefficient(const int degree) const
		{
			assert(degree >= 0);

			return degree <= Degree() ? coefficients[degree] : 0.0;
		}

		inline void SetCoefficient(const int degree, const double value)
		{
			assert(degree >= 0 && degree <= Degree());

			coefficients[degree] = value;
		}
	};

	inline Polynom operator +(const Polynom& a, const Polynom& b)
	{
		const int an = a.Degree() + 1, bn = b.Degree() + 1;
		const int n = std::max(an, bn);

		Polynom ans(0, n - 1);
		
		for(int i = 0; i < n; ++i)
			ans.coefficients[i] =
			((i < an) ? a.coefficients[i] : 0)
			+
			((i < bn) ? b.coefficients[i] : 0);
		
		return ans;
	}

	inline Polynom operator -(const Polynom& a, const Polynom& b)
	{
		const int an = a.Degree() + 1, bn = b.Degree() + 1;
		const int n = std::max(an, bn);

		Polynom ans(0, n - 1);
		
		for(int i = 0; i < n; ++i)
			ans.coefficients[i] =
			((i < an) ? a.coefficients[i] : 0)
			-
			((i < bn) ? b.coefficients[i] : 0);
		
		return ans;
	}

	inline Polynom operator -(const Polynom& a)
	{
		const int n = a.Degree() + 1;

		Polynom ans(0, n - 1);
		
		for(int i = 0; i < n; ++i)
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
		const int an = a.Degree() + 1, bn = b.Degree() + 1;
		const int degree = a.Degree() + b.Degree();

		Polynom ans(0, degree);

		for(int i = 0; i < an; ++i)
			for(int j = 0; j < bn; ++j)
				ans.coefficients[i + j] += a.coefficients[i] * b.coefficients[j];

		return ans;
	}

	inline const Polynom& operator *=(Polynom& a, const Polynom& b)
	{
		return a = a * b;
	}

	inline Polynom operator /(const Polynom& a, const double b)
	{
		const int n = a.Degree() + 1;

		Polynom ans(0, n - 1);

		for(int i = 0; i < n; ++i)
			ans.coefficients[i] = a.coefficients[i] / b;

		return ans;
	}

	inline const Polynom& operator /=(Polynom& a, const double b)
	{
		return a = a / b;
	}
}

#endif
