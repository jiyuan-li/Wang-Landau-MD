
#ifndef FIXNVT_H 
#define FIXNVT_H
#include "Vector.h"
#include "Fix.h"
using namespace std;
class FixNVT : public Fix {
	public:

		FixNVT(vector<Atom *> &allAtoms_, vector<Atom *> atoms_, Data &simData_, double tempTarget_, int applyEvery_) : Fix(allAtoms_, atoms_, simData_, applyEvery_), tempTarget(tempTarget_) {};
		double tempTarget;
		void compute();
};


#endif
