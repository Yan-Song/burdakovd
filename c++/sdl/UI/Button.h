#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <Sprite.h>
#include "Clickable.h"

namespace UI
{
	class Button : public UI::Clickable
	{
	private:
		static const std::string FontName;
		static const int FontSize;

		std::string caption;
		SharedSprite normal, hovered, pressed;

		void updateSprites();

	public:
		Button(SDLApplication* const app, const std::string& caption);
	
		virtual void Render();

	protected:
		virtual void onLayoutChanged();
	};
}

#endif
