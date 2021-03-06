#pragma once

#include "func.h"
#include "logger.h"



double IntegrateRect(Function f, double step, double delta = 0) {

    double res = 0;
    const auto interval = f.GetInterval();

    string filename = "rect_log.csv";
    CSV_LOGGER(filename)

    for (double x = interval.first + delta; x < interval.second; x += step) {
        res += f(x + step / 2) * step;
        LOG(x, f(x))

    }

    return res;
}

double IntegrateTrap(Function f, double step, double delta = 0) {

    double res = 0;
    const auto interval = f.GetInterval();

    string filename = "trap_log.csv";
    CSV_LOGGER(filename)
    

    for (double x = interval.first + delta; x < interval.second; x += step) {
        res += (f(x) + f(x + step)) * step / 2;
        LOG(x, f(x))
    }

    return res;
}

double IntegrateSimpson(Function f, double step, double delta = 0) {

    double res = 0;
    const auto interval = f.GetInterval();

    string filename = "simpson_log.csv";
    CSV_LOGGER(filename)

    for (double x = interval.first + delta; x < interval.second; x += step) {
        res += (f(x) + 4 * f(x + step / 2) + f(x + step)) / 6 * step;
        LOG(x, f(x))

    }

    return res;
}