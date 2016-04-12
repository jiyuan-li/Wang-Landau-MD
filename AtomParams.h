
#ifndef ATOM_PARAMS_H
#define ATOM_PARAMS_H
#include <vector>
using namespace std;


class AtomParams {
	public:
		AtomParams(double sig_, double eps_, double m_) : sig(sig_), eps(eps_), m(m_) {};
		double sig;
		double eps;
		double m;
		int type;
};
//want a little class to make sure params get assigned types nicely
class AtomParamWrapper {
	public:
		vector<AtomParams> params;
		AtomParamWrapper(double rCut_) : rCut(rCut_) {}
		const double rCut;
		AtomParamWrapper &push_back(AtomParams params_) {
			params_.type = params.size();
			params.push_back(params_);
			return *this;
		}
		AtomParams operator [] (int n) {
			return params[n];
		}
};


#endif

