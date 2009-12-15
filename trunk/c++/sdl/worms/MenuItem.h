#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <Sprite.h>
#include <UI/Clickable.h>

class Engine;

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
		MenuItem(Engine* const app, const std::string& text_);

		virtual void Render();

	protected:
		Engine* app;

		void onLayoutChanged();
	};
}

#endif
