
#ifndef FIXLJCUT_H
#define FIXLJCUT_H
#include "InteractionParams.h"
#include "Vector.h"
#include "Fix.h"
using namespace std;
class FixLjCut : public Fix {
	public:
		FixLjCut(vector<Atom *> &allAtoms_, vector<Atom *> atoms_, Data &simData_, InteractionParams &params_, double rCut) : Fix(allAtoms_, atoms_, simData_, 1), params(params_), rCutSqr(rCut*rCut) {};
		InteractionParams params;
		void compute();
		double rCutSqr;
};


#endif
