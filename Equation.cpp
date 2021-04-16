#include "diffeq.h"
#include "profile.h"

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>


const double PRECISION = 0.0001;
const double PRECISION2 = 0.0005;


int main()
{
	LOG_DURATION("SOLVING DIFF EQUATION: ")
	Function f({ 1, 2 });

	SolveEulerAdv(f, 0.01, 1, 1 + sqrt(2));

	return 0;
}