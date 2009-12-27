#ifndef UI_LABEL_H
#define UI_LABEL_h

#include <string>
#include <Color.h>
#include <Font.h>
#include <Sprite.h>
#include "Element.h"

namespace UI
{
	class Label : public UI::Element
	{
	private:
		std::string text;
		SharedFont font;
		Color color;
		SharedSprite image;

		void UpdateSprite();

	public:
		Label(SDLApplication* const, const std::string& , const SharedFont& , const Color& color_ = Palette::Black);

		const std::string& GetText() const;

		SharedFont GetFont() const;

		Color GetColor() const;

		void SetColor(const Color& );

		void SetText(const std::string& newtext);

		void SetFont(const SharedFont& newfont);

		virtual void Render();
	};

	typedef Shared::shared_ptr<UI::Label> SharedLabel;
}

#endif
