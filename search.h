#pragma once

#include <cmath>
#include <utility>
#include <iostream>
#include "func.h"


using Interval = pair<double, double>;

Interval NewtonSearch(double a, double b, double precision);

Interval SimpleIterationSearch(double a, double b, double precision);

Interval BinarySearch(double a, double b, double precision);

Interval SecantSearch(double a, double b, double precision);

Interval NewtonSearch(Function f, double precision);

Interval SimpleIterationSearch(Function f, double precision);

Interval BinarySearch(Function f, double precision);

Interval SecantSearch(Function f, double precision);