#pragma once

#include <string>
#include <cmath>
#include <vector>
#include <exception>

using namespace std;
using Interval = pair<double, double>;

// 1 // x*x*x - x + 1

// 2 // x*x*x - x*x - 9*x + 9;

// 3 // x*x - exp(-x)

// 5 // x*x - 2*x + 1

// 6 // x*x*x - x + 1


class Function {
private:

    double f(double x) {
        return x;               // enter your function here, parsing via console later 
    }

    double phi(double x) {
        return x;               // enter phi-function for IterationSearch
    }

    Interval interval;
    double precision;
    vector<double> deriv_data;

public:
    Function(Interval interval_, double precision_ = 0.01) : precision(precision_), interval(interval_) {

        if (interval.second <= interval.first) {
            throw(invalid_argument("Incorrect interval args"));
        }

        if (abs(precision) < 0.0000001 || precision < 0) {
            throw(invalid_argument("Incorrect precision"));
        }

    }

    double operator() (double x) {

        if (x < interval.first || x > interval.second) {
            throw(out_of_range("x arg out of range"));
        }

        return f(x);
    }

    double Derivative(double x) {
        return (f(x + precision) - f(x - precision) / (2 * precision));         // Not that precise but works fast
    }

    double SecondDerivative(double x) {
        return (Derivative(x + precision) - Derivative(x - precision) / (2 * precision));
    }

    double Phi(double x) {
        return phi(x);
    }

    void DerivativeMemorized() {
        deriv_data.reserve(int(floor(interval.second - interval.first)));

        for (double x = interval.first; abs(interval.second - x) > precision * precision; x += precision) {
            deriv_data.push_back((f(x + precision) - f(x - precision)) / (2 * precision));                          // Dumb method, polynomic soon
        }
    }
};

inline double Func(double x) {
    return x * x - exp(-x);
}

inline double Derivative(double x) {
    return 2 * x + exp(-x);
}

inline double SecondDerivative(double x) {
    return 2 - exp(-x);
}

inline double Phi(double x) {
    return exp(-x)/x;
}