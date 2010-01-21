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
		std::string path;
		SharedSprite normal, hovered, disabled;

		void updateSprites();

		MenuItem(const MenuItem& );
		MenuItem& operator =(const MenuItem& );

	public:
		MenuItem(Engine* const app, const std::string& path_);

		virtual void Render();

	protected:
		Engine* app;

	};
}

#endif
