//
//   This file contains the C++ code from Program 9.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_03.cpp
//
class PrePostVisitor : public Visitor
{
public:
    virtual void PreVisit (Object&) {}
    virtual void Visit (Object&) {}
    virtual void PostVisit (Object&) {}
};

class PreOrder : public PrePostVisitor
{
    Visitor& visitor;
public:
    PreOrder (Visitor& v) : visitor (v)
	{}
    void PreVisit (Object& object)
	{ visitor.Visit (object); }
};

class InOrder : public PrePostVisitor
{
    Visitor& visitor;
public:
    InOrder (Visitor& v) : visitor (v)
	{}
    void Visit (Object& object)
	{ visitor.Visit (object); }
};

class PostOrder : public PrePostVisitor
{
    Visitor& visitor;
public:
    PostOrder (Visitor& v) : visitor (v)
	{}
    void PostVisit (Object& object)
	{ visitor.Visit (object); }
};
