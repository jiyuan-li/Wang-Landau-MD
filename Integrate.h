#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include "Atom.h"
#include <vector>
#include "Run.h"
#include "Fix.h"
using namespace std;
namespace Integrate {
	void verletPreForce(vector<Atom *> &atoms, double timestep);
	void verletPostForce(vector<Atom *> &atoms, double timestep);
	void compute(vector<Fix *> &, int);
	void firstTurn(Run &params);
	void run(Run &params, int currentTurn, int numTurns);
	bool rebuildIsDangerous(vector<Atom *> &atoms, double);
	void addKineticEnergy(vector<Atom *> &, Data &);
	void setThermoValues(Run &);
}

#endif
