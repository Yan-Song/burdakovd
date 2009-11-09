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

		// � ������ ������ callback ��� ����� �������
		// ������� Render ����� ������� ��������� ��� � ������� � ���������� ������� ��������������
		// � ���� �� ������ true �� Render ����� �������
		void Render(SDLApplication* const app, const SharedCallback& callback);
	};
}

#endif
