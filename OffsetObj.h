#ifndef OFFSETOBJ_H
#define OFFSETOBJ_H
#include "Vector.h"
template <class T>
class OffsetObj {
	public:
		T obj;
		Vector offset;
		OffsetObj (T &obj_, Vector offset_) : obj(obj_), offset(offset_) {};
		OffsetObj () : obj(T()), offset(Vector()) {};
};
#endif

