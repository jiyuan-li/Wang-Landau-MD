#ifndef FIX_H
#define FIX_H

#include "Atom.h"
#include "Data.h"
using namespace std;
class Fix {
	public:
		virtual void compute(){};
		vector<Atom *> &allAtoms;
		vector<Atom *> atoms;
		Data &simData;
		int applyEvery;
		virtual void updateAtoms(vector<Atom *> &updatedSet) {};
		virtual void setup(){};
		Fix(vector<Atom *> &allAtoms_, vector<Atom *> &atoms_, Data &simData_, int applyEvery_) : allAtoms(allAtoms_), atoms(atoms_), simData(simData_), applyEvery(applyEvery_) {};
	
};

#endif
