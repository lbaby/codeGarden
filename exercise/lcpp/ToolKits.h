#ifndef TOOLKITS_H_
#define TOOLKITS_H_

#include <Stack.h>
#include <Term.h>
#include <Wrapper.h>
#include <HashTable.h>
#include <BinaryTree.h>
#include <PrePostVisitor.h>
#include <SearchTree.h>

#include <Object.h>

#include <Event.h>
#include <PriorityQueue.h>






template < typename T>
const T & Max(T const &left , T const & right)
{
	return (left > right)?left:right;
}

template < typename T>
const T & Min(T const &left , T const & right)
{
	return (left < right)?left:right;
}

template < typename T>
 void Swap (T &left, T &right)
 {
 	T t = left;
 	left = right;
 	right = t;
 }


void RPNCalculator (Stack& stack);


class Counter : public Int
{
public:
    Counter (int i) : Int (i)
	{}
    void operator ++ ()
	{ ++datum; }
};

class ExpressionTree : public BinaryTree
{
public:
    ExpressionTree (char c) :
	BinaryTree (*new Char (c)) {}
};





void PostfixToInfix ();

void CountWords (HashTable& table);

void TranslateText (SearchTree& dictionary);
void ReadDictionary (SearchTree& dictionary);

void Simulation (PriorityQueue& eventList, doub_time timeLimit);

#endif /*TOOLKITS_H_*/
