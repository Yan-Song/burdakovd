#ifndef CONFIG_H
#define CONFIG_H

// ����� ������ ������ ��������� ����������
struct Config
{
	// � ��������
	static const double MovementTime;
	static const double DiscoverTime;
	// ���������� �������, ������� ����� ������ � ����� ����� ������
	static const double WormEnergyPerCell;
	// ���������� �������, ������� �������� ���� ������ ���
	static const double FoodEnergyPerCell;
	// ������� ������� ������ �� ���� �������
	static const double EnergyLossPerSecond;
	// ���������� ������� ���� �������� ����� ����� �� �����, ����
	static const double DeathEnergyLevel;
	// ���������� �������, ��� ������� ����� �������� ��������
	static const double ReplicateEnergyLevel;
};

#endif
