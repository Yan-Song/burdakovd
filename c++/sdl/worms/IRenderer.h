#ifndef IRENDERER_H
#define IRENDERER_H

#include <Shared.h>
#include <UI/Element.h>

class ISomeWorm;

class IRenderer
{
public:
	virtual void Render(const Shared::shared_ptr<ISomeWorm>& worm, const UI::Element* UIField) const = 0;

	virtual ~IRenderer()
	{
	}
};

typedef Shared::shared_ptr<IRenderer> SharedRenderer;

#endif
