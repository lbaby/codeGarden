//
//   This file contains the C++ code from Program A.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_07.cpp
//
class Person
{
public:
    enum Sex { male, female };
protected:
    std::string name;
    Sex sex;
public:
    std::string Name () const
	{ return name; }
    void Put (std::ostream& s) const
	{ s << name; }
    // ...
};

class Parent : public Person
{
protected:
    unsigned int numberOfChildren;
    Person* child;
public:
    Person& Child (unsigned int i) const
    {
	if (i >= numberOfChildren)
	    throw out_of_range ("invalid child number");
	return child [i];
    }
    void Put (std::ostream& s)
    {
	// ...
    }
    // ...
};
