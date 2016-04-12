#include "FixLjCut.h"


void FixLjCut::compute() {
	double sumEngs = 0;
	Vector virialComps;
	double rCutSqrLoc = rCutSqr;
	for (Atom *a : atoms) {
		int typeA = a->type;
		for (Neighbor &n : a->neighbors) {
			Atom *b = n.obj;
			int typeB = b->type;
			Vector distance = a->pos - (b->pos + n.offset);
			double drSqr = distance.lenSqr();
			if (drSqr < rCutSqrLoc) {
				double ljparam1 = params.getParam1(typeA, typeB); 
				double ljparam2 = params.getParam2(typeA, typeB); 
				double r2inv = 1 / drSqr;
				double r6inv = r2inv*r2inv*r2inv;
				double ljparam3 = params.getParam3(typeA, typeB);
				double ljparam4 = params.getParam4(typeA, typeB);
				double offset = params.getOffset(typeA, typeB);
				double forceScalar = r6inv / drSqr * (ljparam1 * r6inv - ljparam2);
				Vector forceVec = distance * forceScalar;
				a->force += forceVec;
				b->force -= forceVec;
				double eng = r6inv * (ljparam3 * r6inv - ljparam4) - offset;
				sumEngs += eng;
				virialComps += forceVec * distance;

			}
		}
	}
	simData.eng.potential += sumEngs;
	simData.virialTotal += virialComps.sum() / 3;
}
