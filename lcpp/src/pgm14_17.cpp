//
//   This file contains the C++ code from Program 14.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_17.cpp
//
class RandomVariable
{
public:
    virtual double Sample () = 0;
};

class SimpleRV : public RandomVariable
{
public:
    double Sample ();
};

class UniformRV : public RandomVariable
{
    double u;
    double v;
public:
    UniformRV (double _u, double _v) : u (_u), v (_v) {}
    double Sample ();
};

class ExponentialRV : public RandomVariable
{
    double mu;
public:
    ExponentialRV (double _mu) : mu (_mu) {}
    double Sample ();
};
