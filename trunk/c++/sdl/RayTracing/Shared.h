#ifndef SHARED_H
#define SHARED_H

#include <memory>

// ���� ������ ���������� � � �� ��� std::tr1::shared_ptr
// �� ����� ��������� boost, �:
// #include <boost/shared_ptr.hpp>
// using boost::shared_ptr

namespace RT
{
	using std::tr1::shared_ptr;
}

#endif
