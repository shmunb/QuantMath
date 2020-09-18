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

    double f(const double x) const {
        return x * x * x - x + 1;               // enter your function here, parsing via console later 
    }

    double phi(const double x) const {
        return exp(-x)/x;                       // enter phi-function for IterationSearch
    }

    Interval interval;
    double precision;
    vector<double> deriv_data;

public:
    Function(Interval interval_, const double precision_ = 0.001) : precision(precision_), interval(interval_) {

        if (interval.second <= interval.first) {
            throw(invalid_argument("Incorrect interval args"));
        }

        if (abs(precision) < 0.0000001 || precision < 0) {
            throw(invalid_argument("Incorrect precision"));
        }

    }

    double operator() (const double x) const {

        if (x < interval.first - 0.5 || x > interval.second + 0.5) {
            throw(out_of_range("x arg out of range"));
        }

        return f(x);
    }

    double Derivative(const double x) const {

        if (x < interval.first - 0.5 || x > interval.second + 0.5) {
            throw(out_of_range("x arg out of range"));
        }

        return (f(x + precision) - f(x - precision) / (2 * precision));         // Not that precise but works fast
    }

    double SecondDerivative(const double x) const {

        if (x < interval.first - 0.5 || x > interval.second + 0.5) {
            throw(out_of_range("x arg out of range"));
        }

        return (Derivative(x + precision) - Derivative(x - precision) / (2 * precision));
    }

    double HigherDerivative(const int n, const double x) const {    

        if (x < interval.first - 0.5 || x > interval.second + 0.5) {
            throw(out_of_range("x arg out of range"));
        }

        if (n == 0) {
            return f(x);
        }
        else if (n == 1) {
            return Derivative(x);
        }
        else return (HigherDerivative(n - 1, x + precision) - HigherDerivative(n - 1, x - precision) / (2 * precision));
    }

    double Phi(const double x) const{

        if (x < interval.first - 0.5 || x > interval.second + 0.5) {
            throw(out_of_range("x arg out of range"));
        }

        return phi(x);
    }

    Interval GetInterval() const {
        return interval;
    }

    void DerivativeMemorized() {
        deriv_data.reserve(int(floor(interval.second - interval.first)));

        for (double x = interval.first; abs(interval.second - x) > precision * precision; x += precision) {
            deriv_data.push_back((f(x + precision) - f(x - precision)) / (2 * precision));                          // Dumb method, polynomic soon
        }
    }
};

class Polynom : private Function {

    vector<double> _coef;

    double f(double x) {
        double res = 0;
        for (size_t i = 0; i < _coef.size(); ++i) {
            res += _coef[i] * exp(i*log(x)) ;
        }
    }

    double phi(double x) {                              // super dumb implementation of phi
        double res = 0;
        _coef[1]++;
        for (size_t i = 0; i < _coef.size(); ++i) {
            res += _coef[i] * exp(i * log(x));
        }
        _coef[1]--;

        return res;
    
    }
};