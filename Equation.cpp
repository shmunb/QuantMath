#include "integral.h"
#include "profile.h"

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>


const double PRECISION = 0.0001;
const double PRECISION2 = 0.0005;


int main()
{
	LOG_DURATION("INTEGRATED: ")
	double delta = 0.00103;
	Function f({ 0, 1 });
	cout << "Rect: " << IntegrateRect(f, 0.0003, delta) << endl;
	cout << "Trap: " << IntegrateTrap(f, 0.00027, delta)  << endl;
	cout << "Simpson: " << IntegrateSimpson(f, 0.0015, delta)  << endl;
}