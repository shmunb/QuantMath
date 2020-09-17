#pragma once

#include "search.h"

Interval NewtonSearch(double a, double b, double precision) {

    auto start = a;

    while (!Func(start) * SecondDerivative(start) > 0) {
        start += precision;
    }
    while (abs(Func(start)) > precision) {
        start = start - Func(start) / Derivative(start);
    }

    return { start,start };
}

Interval SimpleIterationSearch(double a, double b, double precision) {

    auto start = a; 

    while (abs(Phi(start)) >= 1 && abs(b - start) > precision*precision) {
        start += precision;
    }

    if (start >= b) {
        throw(runtime_error("Phi-functiion doesn't fit"));
    }

    cout << "phi(x0) =" << Phi(start) << ", whith x0 = " << start << endl;

    while (abs(Func(start)) > precision) {
        start = Phi(start);
    }

    return { start,start };
}

Interval SecantSearch(double a, double b, double precision) {

    while (abs(b - a) > precision) {
        if (Func(a) == 0 || Func(b) == 0) {
            cout << "Hit! " << endl;
            break;
        }

        auto point = a + (a - b) * Func(a) / (Func(b) - Func(a));
        Func(point)* Func(a) > 0 ? a = point : b = point;
    }

    return { a , b };
}

Interval BinarySearch(double a, double b, double precision) {

    while (abs(b - a) > precision) {

        if (Func(a) == 0 || Func(b) == 0) {
            cout << "Hit! " << endl;
            break;
        }

        double mid = a + (b - a) / 2;

        Func(mid)* Func(a) > 0 ? a = mid : b = mid;
    }

    return { a , b };
}

Interval NewtonSearch(Function f, double precision = 0.001) {

    double a = f.GetInterval().first;
    double b = f.GetInterval().first;
    auto start = a;

    while (!f(start) * f.SecondDerivative(start) > 0) {
        start += precision;
    }
    while (abs(f(start)) > precision) {
        start = start - f(start) / f.Derivative(start);
    }

    return { start,start };
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