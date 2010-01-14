#ifndef FACTORY_H
#define FACTORY_H

#include "ISomeWorm.h"
#include "IWormFactory.h"

// W должен быть наследником Worm, но как указать это ограничение в шаблоне?
template<class W>
class Factory : public IWormFactory
{
private:
	std::string _ClassName;

public:
	Factory(const std::string& __ClassName) : _ClassName(__ClassName)
	{
	};

	// делать delete для этого указателя возлагается на вызывающего
	virtual SharedSomeWorm Create() const
	{
		return SharedSomeWorm(new W());
	}

	virtual std::string ClassName() const
	{
		return _ClassName;
	}

	virtual ~Factory()
	{
	}
};

#endif
