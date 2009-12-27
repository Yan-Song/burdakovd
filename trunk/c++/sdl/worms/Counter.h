#ifndef UI_COUNTER_H
#define UI_COUNTER_H

#include <Vector.h>
#include <UI/ElementSet.h>

namespace UI
{
	class Counter : public UI::ElementSet
	{
	private:
		class IncrementButton;
		friend class IncrementButton;

		class DecrementButton;
		friend class DecrementButton;

		class Number;
		friend class Number;

		typedef Shared::shared_ptr<IncrementButton> SharedIncrement;
		typedef Shared::shared_ptr<DecrementButton> SharedDecrement;
		typedef Shared::shared_ptr<Number> SharedNumber;

		SharedIncrement inc;
		SharedDecrement dec;
		SharedNumber num;

		void update();

		void increment();

		void decrement();

		int minValue, maxValue, currentValue;

	protected:
		virtual void onLayoutChanged();

	public:
		Counter(SDLApplication* const app, const int min, const int max, const int current, const ScreenPoint LeftBottom);

		int GetValue() const;

		void SetValue(const int value);

	};

	typedef Shared::shared_ptr<UI::Counter> SharedCounter;
}

#endif
