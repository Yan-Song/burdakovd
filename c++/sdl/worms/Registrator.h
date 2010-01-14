#ifndef REGISTRATOR_H
#define REGISTRATOR_H

#include <string>
#include <vector>
#include <Shared.h>
#include "IWormFactory.h"
#include "ISomeWorm.h"

class Registrator
{
private:
	typedef Shared::shared_ptr<IWormFactory> SharedFactory;
	std::vector<SharedFactory> factories;

	inline void Register(const SharedFactory& f)
	{
		factories.push_back(f);
	}

public:
	Registrator();

	// Количество зарегистрированных червяков
	inline size_t Count() const
	{
		return factories.size();
	}

	// имя класса заданного червяка
	inline std::string ClassName(const size_t index) const
	{
		if(index >= factories.size())
			throw new std::out_of_range("ClassName(const size_t index)");

		return factories[index]->ClassName();
	}

	// делать delete для этого указателя возлагается на вызывающего
	inline SharedSomeWorm Create(const size_t ClassID) const
	{
		if(ClassID >= factories.size())
			throw new std::out_of_range("Create(const size_t index)");

		return factories[ClassID]->Create();
	}
};

#endif
