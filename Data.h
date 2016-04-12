#ifndef DATA_H
#define DATA_H

#include "Energy.h"
#include "DataBlockAvgs.h"
class Data {
	public:
		Data() : virialTotal(0) {};
		BlockAvgs avgs;
		Energy eng;
		double virialTotal;
};
#endif
