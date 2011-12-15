//
//   This file contains the C++ code from Program 9.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_21.cpp
//
class ExpressionTree : public BinaryTree
{
public:
    ExpressionTree (char c) :
	BinaryTree (*new Char (c)) {}
};

void PostfixToInfix ()
{
    char c;
    Stack& stack = *new StackAsLinkedList ();

    while (cin >> c, !cin.eof ())
    {
	if (std::isdigit (c) || std::isalpha (c))
	    stack.Push (*new ExpressionTree (c));
	else if (c == '+' || c == '-' || c == '*' || c == '/')
	{
	    ExpressionTree& result = *new ExpressionTree (c);
	    result.AttachRight (
		dynamic_cast<ExpressionTree&> (stack.Pop ()));
	    result.AttachLeft (
		dynamic_cast<ExpressionTree&> (stack.Pop ()));
	    stack.Push (result);
	}
    }
    ExpressionTree& result =
	dynamic_cast<ExpressionTree&> (stack.Pop ());
    InfixVisitor visitor;
    result.DepthFirstTraversal (visitor);
    delete &result;
    delete &stack;
}
