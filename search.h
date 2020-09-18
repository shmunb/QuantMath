#pragma once

#include <cmath>
#include <utility>
#include <iostream>
#include "func.h"


using Interval = pair<double, double>;

Interval NewtonSearch(Function f, double precision);

Interval SimpleIterationSearch(Function f, double precision);

Interval BinarySearch(Function f, double precision);

Interval SecantSearch(Function f, double precision);

int DescartesRootsNumber(Function f, double precision);