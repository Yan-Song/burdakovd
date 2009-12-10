#ifndef IWORMFACTORY_H
#define IWORMFACTORY_H

#include "ISomeWorm.h"
#include <string>

class IWormFactory
{
public:
	IWormFactory()
	{
	}

	virtual SharedSomeWorm Create() const = 0;

	virtual std::string ClassName() const = 0;

	virtual ~IWormFactory()
	{
	};
};

#endif
