#include <string>
#include <iostream>
#include "Bounds.h"
#include "AtomParams.h"
using namespace std;

bool Bounds::atomInBounds(Atom *a) {
	for (int i=0; i<3; i++) {
		if (not (a->pos[i] >= lo[i] and a->pos[i] <= hi[i])) {
			return false;
		}
	}
	return true;
}

double Bounds::volume() {
	return trace.prod();
}

