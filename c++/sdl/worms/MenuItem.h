#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <Sprite.h>
#include <UI/Clickable.h>

namespace UI
{
	class MenuItem : public Clickable
	{
	private:
		std::string text;
		SharedSprite normal, hovered, disabled;

		static const std::string MenuFont;

		void updateSprites();

	public:
		MenuItem(SDLApplication* const app, const std::string& text_);

		virtual void Render();

	protected:
		void onLayoutChanged();
	};
}

#endif
