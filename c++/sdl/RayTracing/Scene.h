#ifndef SCENE_H
#define SCENE_H

#include "CompoundObject.h"
#include "Shared.h"
#include "sdlapplication/Vector.h"

class SDLApplication;

namespace RT
{
	class Scene : protected CompoundObject
	{
	public:
		class ICallback
		{
		public:
			virtual bool call(const double percent) = 0;
			virtual ~ICallback() {}
		};
		typedef shared_ptr<ICallback> SharedCallback;

	public:
		const Point3D SpectatorPosition;

		Scene(const Point3D& _SpectatorPosition) : SpectatorPosition(_SpectatorPosition)
		{
		}

		inline void Add(const CompoundObject::SharedObject& object)
		{
			CompoundObject::Add(object);
		}

		// в данном случае callback это такой функтор
		// который Render будет дергать несколько раз в секунду и передавать процент отрендеренного
		// и если он вернет true то Render будет прерван
		// Quality - качество прорисовки, 1 - максимальное, чем больше  тем ниже качество
		// возвращается true если сцена успела отрендериться до конца, и false если её прервал callback
		bool Render(SDLApplication* const app, const SharedCallback& callback, const int Quality = 1);
	};
}

#endif
