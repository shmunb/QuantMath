#pragma once

#include "diffeq.h"
 

void SolveEulerAdv(Function f, double step, double x, double y) {

	string filename = "adv_euler_log.csv";
	CSV_LOGGER(filename)

	for (x; x < f.GetInterval().second; x += step) {

		LOG(x, y)
		y += step * f(x + step/2, y + step*f(x, y)/2);
	}

}

void SolveEuler(Function f, double step, double x, double y) {

	string filename = "euler_log.csv";
	CSV_LOGGER(filename)	

	for (x; x < f.GetInterval().second; x += step) {

		LOG(x, y);
		y += step * f(x, y);
	}

	return;
}