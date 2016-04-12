#include "Atom.h"
#include "Bounds.h"
#include "AtomGrid.h"
#include "Grid.h"
#include "Vector.h"
#include "Bounds.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "Run.h"
#include "Integrate.h"
#include "Data.h"
#include "includefixes.h"
#include "AtomParams.h"
#include "InteractionParams.h"
#include "InitializeAtoms.h"
using namespace std;
//If using windows, need visual studio 2012 or newer


int main() {
	/*currently this code is set up with two species populating a 15*15*15 box.  Each species is being initialized to occupy about half the box.  
	 *
	 *
	 */
	const double rCut = 2.5;	
	const double padding = 0.5;
	AtomParamWrapper params(rCut);
	params.push_back(AtomParams(1.0, 1.0, 2.0));
	InteractionParams interactionParams(params);
	Bounds region1(Vector(0, 0, 0), Vector(12, 12, 12));

	double gridSize = 3;
	Bounds b(Vector(0, 0, 0), Vector(12, 12, 12));
	Run run(b, interactionParams, gridSize, .005, 5, 6000);
	run.padding = padding;
	run.rCut = params.rCut;
	InitializeAtoms::populateOnGrid(run.atoms, region1, params[0], 346);
	
	double temp = 1.5;
	InitializeAtoms::initTemp(run.atoms, temp);
	
	//declaring fixes.  A fix is just an arbitrary operation that applies forces to atoms
	
	FixLjCut ljForce(run.atoms, run.atoms, run.data, run.params, run.rCut);
	run.fixes.push_back(&ljForce);

	FixNVT constTemp(run.atoms, run.atoms, run.data, temp, 3000);
	run.fixes.push_back(&constTemp);
	
	//end fixes

	const int numTurns = 100000;
	Integrate::run(run, 0, numTurns);

	cout << run.dangerousRebuilds << " dangerous rebuilds " << endl;
}
