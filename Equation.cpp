﻿#include "parser.h"
#include "search.h"
#include "profile.h"
#include "algebra.h"

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>


const double PRECISION = 0.001;
const double PRECISION2 = 0.0005;


int main()
{
   /* string tokens;
    cout << "Enter expression: ";
    getline(cin, tokens);

    int x = 0;
    auto node = Parse(tokens.begin(), tokens.end(), x);

    cout << "Enter x: ";
    while (cin >> x) {
        cout << "Expression value: " << node->Evaluate() << endl;
        cout << "Enter x: ";
    }*/



    //cout << a << ":" << Func(a) <<  " " << b << ":" << Func(a) << endl;

    Matrix<double> m = {
        {1, 2, 3},
        {3, 4, 5},
        {9, 8, 7}
    };

    cout << m << endl; 

    GaussByMainMeaning(m);
    /*Interval res;

    Function f({ -2, -1 }, PRECISION);

    {
        
        LOG_DURATION("Elapsed time: ")
        res = NewtonSearch3(f, PRECISION);
    }
    

    cout << setprecision(6) << res.first << " : " << f(res.first) << endl << res.second << " : " << f(res.second) << endl;*/

}