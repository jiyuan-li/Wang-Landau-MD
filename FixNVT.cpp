#include "FixNVT.h"

void FixNVT::compute() {
	double sumKe = 0;
	double tempTargetLoc = tempTarget;
	for (Atom *a : atoms) {
		sumKe += a->kinetic();
	}
	sumKe /= atoms.size() * 3.0 / 2.0;
	for (Atom *a : atoms) {
		a->vel *= sqrt(tempTargetLoc / sumKe);
	}

}
