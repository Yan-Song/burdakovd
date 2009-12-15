#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "MouseOverable.h"

namespace UI
{
	class Clickable : public MouseOverable
	{
	private:
		bool halfClicked;

	protected:
		// ���������� � ������ ������� ����� ������ ���� � �������� �������� ����������
		virtual void onMouseDown();

		// ���������� � ������ ���������� ����� ������ ���� � �������� �������� ����������
		// ��� �������, ��� ������ ��� ���� ����� ��� ���� ���������
		virtual void onMouseUp();

		// ���������� ��� ������� � ���������� ����� ������ ���� ��� ��������� ����������
		// ����� ����� ����� ��������� ��������� ���� ��� �������� �� ������� ��������
		virtual void onClick();

		// "�����" �� ������ ������� ����������
		// ������� � ��� ������ ���� ��� ���� ������ ��� ���� ���������
		// � ������ ��������� ��� ���, � ��� �� ��������
		// ����� �������������� ��� ��������� ���������� "��������" � "�� ��������" �������� ����������
		virtual bool isElementPressed() const;

	public:
		Clickable(SDLApplication* const app);

		virtual void ProcessEvent(const SDL_Event& Event);
	};
}

#endif
