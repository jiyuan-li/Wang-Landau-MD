#ifndef INITIALIZE_H
#define INTIIALIZE_H
#include "Bounds.h"
#include "Atom.h"
#include "AtomParams.h"
#include <math.h>
#include <vector>
#include <random>
#include <map>
using namespace std;

namespace InitializeAtoms {
	void populateOnGrid(vector<Atom *> &atoms, Bounds &b, AtomParams params, int n) {
		assert(n>=0);
		int numFinal = atoms.size() + n;
		int nPerSide = ceil(pow(n, 1.0/3.0));
		Vector deltaPerSide = b.trace / nPerSide;
		for (int i=0; i<nPerSide; i++) {
			for (int j=0; j<nPerSide; j++) {
				for (int k=0; k<nPerSide; k++) {
					if ((int) atoms.size() == numFinal) {
						return;
					}
					int id = 0;
					if (atoms.size()) {
						id = atoms[atoms.size()-1]->id + 1;
					}
					Vector pos = b.lo + Vector(i, j, k) * deltaPerSide;
					Atom *a = new Atom(pos, params.m, params.type, id);
					atoms.push_back(a);

				}
			}
		}
	}
	void initTemp(vector<Atom *> &atoms, double temp) { //boltzmann const is 1 for reduced lj units
		default_random_engine generator;
		map<double, normal_distribution<double> > dists;
		for (Atom *a : atoms) {
			if (dists.find(a->m) == dists.end()) {
				dists[a->m] = normal_distribution<double> (0, sqrt(temp / a->m));
			}
		}
		Vector sumVels;
		for (Atom *a : atoms) {
			for (int i=0; i<3; i++) {
				a->vel[i] = dists[a->m](generator);
			}
			sumVels += a->vel;
		}
		sumVels /= (double) atoms.size();
		double sumKe = 0;
		for (Atom *a : atoms) {
			a->vel -= sumVels;
			sumKe += a->kinetic();
		}
		double curTemp = sumKe * 2.0 / 3.0 / atoms.size();
		for (Atom *a : atoms) {
			a->vel *= sqrt(temp / curTemp);
		}

		
	}
}

#endif
