#ifndef RUNPARAMS_H
#define RUNPARAMS_H

#include "Atom.h"
#include "AtomGrid.h"
#include "Fix.h"
#include <vector>
#include "Data.h"
#include "InteractionParams.h"
using namespace std;
/*
 * run owns atoms, data, and fixes -  All that it sees.
 * AtomGrid has a reference to atoms, operates on those.  Shouldn't slow things down much b/c using iterators
 * Fixes have a reference to the list of all atoms along with a list of atoms that they are operating on
 * Fixes also have a reference to data
*/
class Run {
	public:
		Run(Bounds b, InteractionParams &params_, double gridSize, double timestep_, int neighborListInterval_, int dataInterval_) : params(params_), grid(atoms, b, gridSize, gridSize, gridSize), timestep(timestep_), neighborListInterval(neighborListInterval_), dataInterval(dataInterval_), dangerousRebuilds(0), currentTurn(0) {
			periodic[0] = periodic[1] = periodic[2] = true;
		};

		vector<Atom *> atoms;
		vector<Fix *> fixes;
		InteractionParams params;
		AtomGrid grid;
		double rCut;
		double padding;
		double timestep;
		bool periodic[3];
		int neighborListInterval; //check for re-neighborlisting every # turns
		int dataInterval;
		Data data;
		int dangerousRebuilds;
		int currentTurn;

};

#endif
