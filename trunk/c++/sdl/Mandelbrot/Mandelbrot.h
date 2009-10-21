#include "SDLApplication.h"
#include "Color.h"
#include <complex>

typedef std::complex<double> Complex;

class Mandelbrot :
	public SDLApplication
{
private:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int ColorDepth = 0, SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT;
	long long lasttime, lastframes;
	double k, bx, by;
	bool needReDraw;
	int ops;

	Color GetColor(const Complex& c, int depth);

	void DoNavigation();

protected:
	virtual void Main();

	virtual void Render();

	virtual void ProcessEvent(SDL_Event);

public:
	Mandelbrot(void);

	virtual ~Mandelbrot(void);
};
