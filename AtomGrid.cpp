#include "AtomGrid.h"


void AtomGrid::appendNeighborList(Atom *a, OffsetObj<Atom **> &gridSqr, double threshSqr) {
	if (*gridSqr.obj != (Atom *) NULL) {
		Vector offset = gridSqr.offset;
		Atom *current;
		for (current = *gridSqr.obj; current != (Atom *)NULL; current = current->next) {
			if (a->pos.distSqr(current->pos + offset) <= threshSqr) {
				a->neighbors.push_back(Neighbor(current, offset));	
			}
		}
	}
}

void AtomGrid::enforcePeriodic() { //make it so doesn't loop in finite dimensions
	Vector lo = bounds.lo;
	Vector hi = bounds.hi;
	Vector trace = bounds.trace;
	for (Atom *a : atoms) {
		Vector prev = a->pos;
		for (int i=0; i<3; i++) {
			if (a->pos[i] < lo[i]) {
				a->pos[i] += trace[i];
			} else if (a->pos[i] >= hi[i]) {
				a->pos[i] -= trace[i];
			}
			//IF YOU GET MYSTERIOUS CRASHES, THERE MAY BE FLOATING POINT ERROR WHERE ADDING/SUBTRACTING TRACE PUTS IT SLIGHTLY OFF OF THE GRID
		}
		if (!bounds.atomInBounds(a)) {
			cout << prev.asStr() << endl;
			cout << "Atom id " << a->id << " moved more than one box length since building neighbor lists.  Program about to quit.  Consider decreasing your neighboring interval" << endl;
			assert(false);
		}
	}
}

void AtomGrid::updateAtoms(vector<Atom *> &atoms_) {
	atoms = atoms_;
}

void AtomGrid::buildNeighborLists(double thresh, bool loops[3]) { //grid size must be >= 2*thresh
	double threshSqr = thresh*thresh;
	for (Atom *a : atoms) {
		a->neighbors.erase(a->neighbors.begin(), a->neighbors.end()); 
		a->posAtNeighborListing = a->pos;
	}
	reset();
	/*
	*using looping values, make list of squares that corresponds to the neighbors for each square.
	 Then for each atom, add atoms by following each linked list and appening those within rcut
	*/ 
	vector<vector<OffsetObj<Atom **> > > neighborSquaress;
	neighborSquaress.reserve(raw.size());
	for (int i=0; i<ns[0]; i++) {
		for (int j=0; j<ns[1]; j++) {
			for (int k=0; k<ns[2]; k++) {
				int coord[3];
				coord[0] = i; coord[1] = j; coord[2] = k;
				neighborSquaress.push_back(getNeighbors(coord, loops, bounds.trace));
			}
		}
	}
	for (Atom *a : atoms) {
		int idx = idxFromPos(a->pos);		
		Atom **neighborSquare = &(*this)(a->pos);
		OffsetObj<Atom **> selfSquare = OffsetObj<Atom **>(neighborSquare, Vector(0, 0, 0));
		appendNeighborList(a, selfSquare, threshSqr);
		a->next = *selfSquare.obj;
		*selfSquare.obj = a;
		vector<OffsetObj<Atom **> > &neighborSquares = neighborSquaress[idx];
		for (OffsetObj<Atom **> &neighborSquare : neighborSquares) {
			appendNeighborList(a, neighborSquare, threshSqr);	
		}
	}
	//atoms[0]->neighbors
}

