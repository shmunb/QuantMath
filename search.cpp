#pragma once

#include "search.h"

Interval NewtonSearch(Function f, double precision = 0.001) {

    double a = f.GetInterval().first;
    double b = f.GetInterval().first;
    auto start = a;

    while (!f(start) * f.SecondDerivative(start) > 0) {             // Newton Condition
        start += precision;
    }
    while (abs(f(start)) > precision) {
        start = start - f(start) / f.Derivative(start);
    }

    return { start,start };
}



// xn - f/f' - f''*f^2/2f'^3
// | f*f'' - f'''*f^2/2f'^3 - f''*(f/f'^2 - 3f^2*/2f'^4) | < 1
// abs(f(x)*f(x)*(f.HigherDerivative(3, x)*f.Derivative(x) - 3*f.SecondDerivative(x)*f.SecondDerivative(x))/(2*exp(4*log(f.Derivative(x)))))


Interval NewtonSearch3(Function f, double precision) {
    double a = f.GetInterval().first;
    double b = f.GetInterval().first;
    auto x = a;

    while ( abs(f(x) * f(x) * (f.HigherDerivative(3, x) * f.Derivative(x) - 3 * f.SecondDerivative(x) * f.SecondDerivative(x))                      // Newton Condition
                        / (2 * exp(4 * log(f.Derivative(x))))) > 1 ) 
    {  x += precision;  }

    while (abs(f(x)) > precision) {
        x = x - f(x) / f.Derivative(x) - f.SecondDerivative(x)*f(x)*f(x)/(2* f.Derivative(x) * f.Derivative(x) * f.Derivative(x));
    }

    return { x,x };
}

Interval SimpleIterationSearch(Function f, double precision = 0.001) {
    return { 0,0 };
}

Interval BinarySearch(Function f, double precision = 0.001) {

    double a = f.GetInterval().first;
    double b = f.GetInterval().first;

    while (abs(b - a) > precision) {

        if (f(a) == 0 || f(b) == 0) {
            cout << "Hit! " << endl;
            break;
        }

        double mid = a + (b - a) / 2;

        f(mid)* f(a) > 0 ? a = mid : b = mid;
    }

    return { a , b };
}

Interval SecantSearch(Function f, double precision = 0.001) {

    double a = f.GetInterval().first;
    double b = f.GetInterval().first;

    while (abs(b - a) > precision) {
        if (f(a) == 0 || f(b) == 0) {
            cout << "Hit! " << endl;
            break;
        }

        auto point = a + (a - b) * f(a) / (f(b) - f(a));
        f(point)* f(a) > 0 ? a = point : b = point;
    }

    return { a , b };
}

int DescartesRootsNumber(Function f, double precision) {

    vector<double> Fa(8, 0);              // Stourm's series for function
    vector<double> Fb(8, 0);



    return 0;
}