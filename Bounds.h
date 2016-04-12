#ifndef BOUNDS_H
#define BOUNDS_H
#include <stdio.h>
#include "Atom.h"
#include "BoundsGeneric.h"
#include "AtomParams.h"
#include <assert.h>
using namespace std;
class Bounds : public BoundsGeneric {
	public:
		Bounds() {

		}
		Bounds(Vector &lo_, Vector &hi_) : BoundsGeneric(lo_, hi_) {
		}
		Bounds(Vector lo_, Vector hi_) : BoundsGeneric(lo_, hi_) {
		}
		
		string asStr() {
			
			string loStr = "Lower bounds " + lo.asStr();
			string hiStr = "upper bounds " + hi.asStr();
			return loStr + ", " + hiStr ;
		}
		bool atomInBounds(Atom *);
		double volume();
	

};


#endif
