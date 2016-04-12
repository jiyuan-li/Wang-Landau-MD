#ifndef INTERACTION_PARAMS_H
#define INTERACTION_PARAMS_H
#include <math.h>
#include "AtomParams.h"
#include <iostream>
//class for getting atom interaction parameters for force computation.  
//Implemented completely in header so that can be inlined
using namespace std;
class InteractionParams {
	public:
		InteractionParams(){};
		InteractionParams(AtomParamWrapper &wrapper) : numTypes(wrapper.params.size()) {
			populate(wrapper);
		};
		vector<double> param1; //mapping 2d array into 1d list
		vector<double> param2; //param1 for r^12 term, param2 for r^6 term
		vector<double> param3;
		vector<double> param4;
		vector<double> offset;
		int numTypes;
		//not many types, so n^2 size list isn't so bad, and makes it so getting params is faster than from list that's not redundant 
		void populate(AtomParamWrapper &wrapper) {
			numTypes = wrapper.params.size();
			vector<AtomParams> params = wrapper.params;
			for (int i=0; i<numTypes; i++) {
				for (int j=0; j<numTypes; j++) {
					AtomParams &a = params[i];
					AtomParams &b = params[j];
					double sig = (a.sig + b.sig) / 2;
					double eps = sqrt(a.eps * b.eps);
					double p1 = eps * 48 * pow(sig, 12);
					double p2 = eps * 24 * pow(sig, 6);
					double p3 = eps * 4 * pow(sig, 12);
					double p4 = eps * 4 * pow(sig, 6);
					double offsetRatio = sig / wrapper.rCut;
					double offsetVal =	4 * eps * (pow(offsetRatio, 12) - pow(offsetRatio, 6));
					param1.push_back(p1);
					param2.push_back(p2);
					param3.push_back(p3);
					param4.push_back(p4);
					offset.push_back(offsetVal);
				}
			}
		}
		double getParam1(int i, int j) { //order doesn't matter, array is symmetric around diagonal
			return param1[i * numTypes + j];
		}
		double getParam2(int i, int j) {
			return param2[i * numTypes + j];
		}
		double getParam3(int i, int j) {
			return param3[i * numTypes + j];
		}
		double getParam4(int i, int j) {
			return param4[i * numTypes + j];
		}
		double getOffset(int i, int j) {
			return offset[i * numTypes + j];
		}
};

#endif
