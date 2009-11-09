#ifndef SCENE_H
#define SCENE_H

#include "CompoundObject.h"
#include "Shared.h"

class SDLApplication;

namespace RT
{
	class Scene : protected CompoundObject
	{
	private:

	public:
		class ICallback
		{
		public:
			virtual bool call(const double percent) = 0;
			virtual ~ICallback() {}
		};

		typedef shared_ptr<ICallback> SharedCallback;

		inline void Add(const CompoundObject::SharedObject& object)
		{
			CompoundObject::Add(object);
		}

		// в данном случае callback это такой функтор
		// который Render будет дергать несколько раз в секунду и передавать процент отрендеренного
		// и если он вернет true то Render будет прерван
		void Render(SDLApplication* const app, const SharedCallback& callback);
	};
}

#endif
