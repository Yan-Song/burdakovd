#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <sdlapplication/Color.h>
#include <sdlapplication/Shared.h>
#include <sdlapplication/Vector.h>
#include "CompoundObject.h"
#include "IEngine.h"
#include "Light.h"
#include "NormalizedVector3D.h"

class SDLApplication;

namespace RT
{
	class Scene : protected CompoundObject, public IEngine
	{
	public:
		typedef Shared::shared_ptr<Light> SharedLight;

	private:
		typedef std::vector<RealColor> ColorContainer;
		typedef std::vector<SharedLight> LightContainer;

		ColorContainer buffer;
		LightContainer lights;
		RealColor ambient;

		void DrawBuffer(SDLApplication* const app, const bool rectangles, const unsigned int Quality);

	public:
		class ICallback
		{
		public:
			virtual bool call(const double percent) = 0;
			virtual ~ICallback() {}
		};
		typedef Shared::shared_ptr<ICallback> SharedCallback;

	public:
		Point3D SpectatorPosition;

		Scene(const Point3D& _SpectatorPosition) : buffer(), lights(), ambient(0.0, 0.0, 0.0), SpectatorPosition(_SpectatorPosition)
		{
		}

		inline void Add(const CompoundObject::SharedObject& object)
		{
			CompoundObject::Add(object);
		}

		// излучение точечного источника ослабевает с расстоянием квадратично
		// таким образом для того чтобы точечный источник на расстоянии 1000 единиц
		// давал такую же яркость что и ambient
		// он должен иметь мощность в 1000000 раз больше
		inline void AddLight(const SharedLight& light)
		{
			lights.push_back(light);
		}

		// установить рассеянное освещение, которое дейсвует на любые поверхности, не зависимо от их положения и нормали
		inline void SetAmbient(const RealColor& _ambient)
		{
			ambient = _ambient;
		}

		// в данном случае callback это такой функтор
		// который Render будет дергать несколько раз в секунду и передавать процент отрендеренного
		// и если он вернет true то Render будет прерван
		// Quality - качество прорисовки, 1 - максимальное, чем больше  тем ниже качество
		// возвращается true если сцена успела отрендериться до конца, и false если её прервал callback
		bool Render(SDLApplication* const app, const SharedCallback& callback, const unsigned int Quality = 1,
			const bool rectangles = true);

		virtual RealColor CalculateLightness(const Point3D& point, const NormalizedVector3D& n) const;
	};
}

#endif
