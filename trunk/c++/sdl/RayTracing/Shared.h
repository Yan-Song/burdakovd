#ifndef SHARED_H
#define SHARED_H

#include <tr1/memory>

// если старый компилятор и в нём нет std::tr1::shared_ptr
// то можно поставить boost, и:
// #include <boost/shared_ptr.hpp>
// using boost::shared_ptr

namespace RT
{
	using std::tr1::shared_ptr;
}

#endif
