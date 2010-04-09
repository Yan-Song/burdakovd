#include <cmath>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct pat
{
	int patient, departure;

	pat() : patient(-1), departure(0)
	{
	}

	pat(const int patient_, const int departure_) : patient(patient_), departure(departure_)
	{
	}

	bool empty() const
	{
		return patient == -1;
	}
};

struct Vector
{
	double x, y;

	Vector() : x(0.0), y(0.0)
	{
	}

	Vector(const double x_, const double y_) : x(x_), y(y_)
	{
	}

	double qsize() const
	{
		return x * x + y * y;
	}
};

Vector operator -(const Vector& a, const Vector& b)
{
	return Vector(a.x - b.x, a.y - b.y);
}

Vector operator +(const Vector& a, const Vector& b)
{
	return Vector(a.x + b.x, a.y + b.y);
}

istream& operator >>(istream& is, Vector& v)
{
	return is >> v.x >> v.y;
}

int main()
{
	int tc; cin >> tc;

	for(int ti = 1; ti <= tc; ++ti)
	{
		int p, s, v;

		cin >> p >> s >> v;

		vector<vector<bool> > near(s, vector<bool>(s, false));

		vector<Vector> coords(s);

		for(int i = 0; i < s; ++i)
			cin >> coords[i];

		for(int i = 0; i < s; ++i)
			for(int j = 0; j < i; ++j)
			{
				if((coords[i] - coords[j]).qsize() <= 4.0)
				{
					near[i][j] = true;
					near[j][i] = true;
				}
			}

		
		vector<pat> seats;
		
		for(int i = 0; i < v; ++i)
		{
			int pi, ai, di;

			scanf("%d %d %d", &pi, &ai, &di);

			// освободить места
			int m = -1;
			for(int i = 0; i < s; ++i)
			{
				if(seats[i].departure <= ai)
					seats[i] = pat();

				if(m == -1 && seats[i].empty())
					m = i;
			}

			

		}
	}

	return 0;
}
