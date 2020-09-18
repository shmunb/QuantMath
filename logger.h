#pragma once

#include <fstream>
#include <iomanip>
#include <string>


#define CSV_LOGGER(_file)					 \
	ofstream output(_file, ofstream::app);   \
	output << "Iter" << ';' << "x" << ';' << "y" << endl;			 \
	output.close();

#define LOG(_file, _x, _y, _iter)					   \
	ofstream output(_file, ofstream::app);			   \
	output << setprecision(8) <<_iter << ';' << _x << ';' << _y << endl;  \
	output.close();