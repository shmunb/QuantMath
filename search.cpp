#pragma once

#include "search.h"

Interval NewtonSearch(Function f, double precision = 0.001) {

    double a = f.GetInterval().first;
    double b = f.GetInterval().first;
    auto start = a;


    string filename = "newton_log.csv";
    CSV_LOGGER(filename)
    size_t i = 0;

    while (f(start) * f.SecondDerivative(start) < 0.1) {             // Newton Condition
        start += 0.1;
    }
    while (abs(f(start)) > precision) {

        ++i;
        start = start - f(start) / f.Derivative(start);
        LOG (filename, start, f(start), i)
    }

    return { start,start };
}

// xn - f/f' - f''*f^2/2f'^3
// | f*f'' - f'''*f^2/2f'^3 - f''*(f/f'^2 - 3f^2*/2f'^4) | < 1
// abs(f(x)*f(x)*(f.HigherDerivative(3, x)*f.Derivative(x) - 3*f.SecondDerivative(x)*f.SecondDerivative(x))/(2*exp(4*log(f.Derivative(x)))))


Interval NewtonSearch3(Function f, double precision = 0.0001) {
    double a = f.GetInterval().first;
    double b = f.GetInterval().first;
    auto x = a;

    while ( abs(f(x) * f(x) * (f.HigherDerivative(3, x) * f.Derivative(x) - 3 * f.SecondDerivative(x) * f.SecondDerivative(x))                      // Newton Condition
                        / (2 * exp(4 * log(f.Derivative(x))))) > 1 ) 
    {  x += precision;  }

    string filename = "newton3_log.csv";
    CSV_LOGGER(filename)    
    size_t i = 0;
    
    while (abs(f(x)) > precision) {
        
        x = x - f(x) / f.Derivative(x) - f.SecondDerivative(x)*f(x)*f(x)/(2* f.Derivative(x) * f.Derivative(x) * f.Derivative(x));
        ++i;
        LOG(filename, x, f(x), i)
    }

    return { x,x };
}

Interval SimpleIterationSearch(Function f, double precision = 0.0001) {

    double a = f.GetInterval().first;
    double b = f.GetInterval().first;
    auto start = a;


    string filename = "iteration_log.csv";
    CSV_LOGGER(filename)
    size_t i = 0;

    while (abs(f.Phi(start + precision) - f.Phi(start - precision))/(2*precision) > 1) {             // SI Condition
        start += precision;
    }

    while (abs(f(start)) > precision) {
        ++i;
        start = f.Phi(start);
        LOG(filename, start, f(start), i)
    }



    return { start, start };
}

Interval BinarySearch(Function f, double precision = 0.0001) {

    double a = f.GetInterval().first;
    double b = f.GetInterval().second;

    string filename = "binary_log.csv";
    size_t i = 0;
    CSV_LOGGER(filename)

    while (abs(b - a) > precision) {
        ++i;
        if (f(a) == 0 || f(b) == 0) {
            cout << "Hit! " << endl;
            break;
        }

        double mid = a + (b - a) / 2;

        f(mid)* f(a) > 0 ? a = mid : b = mid;

        LOG(filename, mid, f(mid), i)
    }

    return { a , b };
}

Interval SecantSearch(Function f, double precision = 0.0001) {

    double a = f.GetInterval().first;
    double b = f.GetInterval().first;

    string filename = "secant_log.csv";
    size_t i = 0;
    CSV_LOGGER(filename)

    while (abs(b - a) > precision) {
        if (f(a) == 0 || f(b) == 0) {
            cout << "Hit! " << endl;
            break;
        }

        auto point = a + (a - b) * f(a) / (f(b) - f(a));
        f(point)* f(a) > 0 ? a = point : b = point;

        LOG(filename, point, f(point), i)
    }

    return { a , b };
}

int DescartesRootsNumber(Function f, double precision) {

    vector<double> Fa(8, 0);              // Stourm's series for function
    vector<double> Fb(8, 0);



    return 0;
}