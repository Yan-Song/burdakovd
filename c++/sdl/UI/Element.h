#ifndef ELEMENT_H
#define ELEMENT_H

#include <ISimpleGameLoop.h>

namespace UI
{
	class Element : public ISimpleGameLoop
	{
	private:
		int width, height, left, bottom;

	public:
		Element(const int width_ = 0, const int height_ = 0)
			: width(width_), height(height_), left(0), bottom(0) {}

		virtual int GetWidth() const;

		virtual int GetHeight() const;

		virtual int GetLeft() const;

		virtual int GetBottom() const;

		virtual void SetWidth(const int w);

		virtual void SetHeight(const int h);

		virtual void SetLeft(const int l);

		virtual void SetBottom(const int b);

		virtual void ProcessEvent(const SDL_Event& );

		virtual void Main();

		virtual void Render();
	};
}

#endif
