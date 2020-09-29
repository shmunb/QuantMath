#pragma once

#include <fstream>
#include <iomanip>
#include <string>

const string DIR = "./results/";

#define CSV_LOGGER(_file)									  \
	ofstream output(DIR + _file);   \
	output << "Iter" << ',' << "x" << ',' << "y" << endl;	  \
	output.close();

#define LOG(_file, _x, _y, _iter)										  \
	ofstream output(DIR + _file, ofstream::app);				  \
	output << setprecision(8) <<_iter << ',' << _x << ',' << _y << endl;  \
	output.close();