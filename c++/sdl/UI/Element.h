#ifndef ELEMENT_H
#define ELEMENT_H

#include <stack>
#include <ISimpleGameLoop.h>
#include <Vector.h>

class SDLApplication;

namespace UI
{
	class Element : public ISimpleGameLoop
	{
	private:
		std::stack<SDL_Rect> clipStack;
		int width, height, left, bottom;
		bool enabled;

		Element(const Element& );
		Element& operator =(const Element& );

	protected:
		SDLApplication* app;

		void Clip();

		void UnClip();

	public:
		Element(SDLApplication* const app_)
			: clipStack(), width(0), height(0), left(0), bottom(0), enabled(true), app(app_) {}

		virtual int GetWidth() const;

		virtual int GetHeight() const;

		virtual int GetLeft() const;

		virtual int GetBottom() const;

		virtual bool Enabled() const;

		virtual void SetWidth(const int w);

		virtual void SetHeight(const int h);

		virtual void SetLeft(const int l);

		virtual void SetBottom(const int b);

		virtual void SetCenter(const ScreenPoint& center);

		virtual void SetEnabled(const bool);

		virtual void Enable();

		virtual void Disable();

		virtual void ProcessEvent(const SDL_Event& );

		virtual void Main();

		virtual void Render();

		virtual ScreenPoint GetCenter() const;

		virtual ScreenPoint GetLeftBottom() const;

		virtual void Maximize();

	protected:
		virtual void onLayoutChanged();
	};

	typedef Shared::shared_ptr<Element> SharedElement;
}

#endif