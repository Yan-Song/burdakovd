#ifndef SHARED_H
#define SHARED_H

#ifdef TR1_PREFIX
#include <tr1/memory>
#else
#include <memory>
#endif

// если старый компилятор и в нём нет std::tr1::shared_ptr
// то можно поставить boost, и:
// #include <boost/shared_ptr.hpp>
// using boost::shared_ptr

namespace Shared
{
	using std::tr1::shared_ptr;
}

#endif
