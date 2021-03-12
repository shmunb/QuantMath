#pragma once

#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

const string DIR = "./results/";

class Logger {
	ostringstream data;
	size_t iter = 0;
	string file;

public:
	explicit Logger(string& _file) {
		file = DIR + move(_file);
		data << "Iter" << ',' << "x" << ',' << "y" << endl;
	}

	void tick(const double _x, const double _y) {
		data << setprecision(6) << iter << ',' << _x << ',' << _y << endl;
		iter++;
	}

	~Logger() {
		ofstream output(file);
		output << data.rdbuf();
	}
};

#define CSV_LOGGER(_file)									  \
	Logger logger(_file);

#define LOG(_x, _y)										  \
	logger.tick(_x, _y);