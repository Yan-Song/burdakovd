#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <sdlapplication/Color.h>
#include <sdlapplication/Shared.h>
#include <sdlapplication/Utils.h>
#include <sdlapplication/Vector.h>
#include "CompoundObject.h"
#include "ICamera.h"
#include "IEngine.h"
#include "Light.h"
#include "NormalizedVector3D.h"
#include "Ray.h"

class SDLApplication;

namespace RT
{
	class Scene : protected CompoundObject, public IEngine
	{
	public:
		typedef Shared::shared_ptr<ILight> SharedLight;
		typedef Shared::shared_ptr<ICamera> SharedCamera;

	private:
		typedef std::vector<RealColor> ColorContainer;
		typedef std::vector<SharedLight> LightContainer;

		ColorContainer buffer;
		LightContainer lights;
		SharedCamera camera;
		RealColor ambient;
		double MinimumRayPower;

		void DrawBuffer(SDLApplication* const app, const bool rectangles, const unsigned int Step);

	public:
		class ICallback
		{
		public:
			virtual bool call(const double percent) = 0;
			virtual ~ICallback() {}
		};
		typedef Shared::shared_ptr<ICallback> SharedCallback;

	public:
		Scene() : buffer(), lights(), camera(), ambient(0.0, 0.0, 0.0), MinimumRayPower(1.0)
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

		// Установить минимальную мощность луча, при которой его ещё стоит трассировать
		// от 0.0 до 1.0
		// чем значение меньше, тем дольше будет рендеринг, но качественнее отражения
		// в 0.0 не ставить, это приведёт к вечному циклу
		inline void SetMinimumRayPower(const double power)
		{
			assert(power > 0);
			MinimumRayPower = power;
		}

		inline void SetCamera(const SharedCamera& _camera)
		{
			camera = _camera;
		}

		// в данном случае callback это такой функтор
		// который Render будет дергать несколько раз в секунду и передавать процент отрендеренного
		// и если он вернет true то Render будет прерван
		// Step - шаг прорисовки, 1 - наилучшее качество, если больше то быстрее но ниже качество
		// возвращается true если сцена успела отрендериться до конца, и false если её прервал callback
		// extra - для рассчета цвета каждого пикселя испускается extra * extra лучей и затем берётся среднее
		// чем extra больше - тем меньше ступенчатость, но дольше рендерится, минимальное значение 1
		bool Render(SDLApplication* const app, const SharedCallback& callback, const unsigned int Step = 1,
			const bool rectangles = true, const unsigned int extra = 1);


		// IEngine members

		virtual RealColor CalculateLightness(const Point3D& point, const NormalizedVector3D& n) const;

		virtual RealColor Trace(const RT::Ray& ray) const;
	};
}

#endif
