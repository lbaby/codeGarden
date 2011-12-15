//
//   This file contains the C++ code from Program A.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_02.cpp
//
void Two (int& x)
{
    x = 2;
    cout << x << endl;
}

void One ()
{
    int y = 1;
    Two (y);
    cout << y << endl;
}
