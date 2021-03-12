#pragma once

#include <string>
#include <cmath>
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;
using Interval = pair<double, double>;



class Function {
private:

    double f(const double x) const {
        return  log(1 + x * x) / (x * sqrt(x));             // enter your function here, parsing via console later 
    }

    double phi(const double x) const {
        return atan(x - 1)/2;                       // enter phi-function for IterationSearch
    }

    Interval interval;
    double precision;

public:
    Function(Interval interval_, const double precision_ = 0.0001) : precision(precision_), interval(interval_) {

        if (interval.second <= interval.first) {
            throw(invalid_argument("Incorrect interval args"));
        }

        if (abs(precision) < 0.000000001 || precision < 0) {
            throw(invalid_argument("Incorrect precision"));
        }

    }

    double operator() (const double x) const {

        /*if (x < interval.first - 0.5 || x > interval.second + 0.5) {
            throw(out_of_range("x arg out of range"));
        }*/

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

        /*if (x < interval.first - 0.5 || x > interval.second + 0.5) {
            throw(out_of_range("x arg out of range"));
        }*/

        return phi(x);
    }



    Interval GetInterval() const {
        return interval;
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