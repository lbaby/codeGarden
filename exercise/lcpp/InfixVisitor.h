#ifndef INFIXVISITOR_H_
#define INFIXVISITOR_H_

#include <iostream>


class InfixVisitor : public PrePostVisitor
{
public:
    void PreVisit (Object&)
	{ std::cout << "("; }
    void Visit (Object& object)
	{ std::cout << object; }
    void PostVisit (Object&)
	{ std::cout << ")"; }
};

#endif /*INFIXVISITOR_H_*/
