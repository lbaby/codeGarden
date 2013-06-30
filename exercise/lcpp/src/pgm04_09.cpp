//
//   This file contains the C++ code from Program 4.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_09.cpp
//
template <class T>
class LinkedList;

template <class T>
class ListElement
{
    T datum;
    ListElement* next;

    ListElement (T const&, ListElement*);
public:
    T const& Datum () const;
    ListElement const* Next () const;

    friend LinkedList<T>;
};

template <class T>
class LinkedList
{
    ListElement<T>* head;
    ListElement<T>* tail;
public:
    LinkedList ();
    ~LinkedList ();

    LinkedList (LinkedList const&);
    LinkedList& operator = (LinkedList const&);

    ListElement<T> const* Head () const;
    ListElement<T> const* Tail () const;
    bool IsEmpty () const;
    T const& First () const;
    T const& Last () const;

    void Prepend (T const&);
    void Append (T const&);
    void Extract (T const&);
    void Purge ();
    void InsertAfter (ListElement<T> const*, T const&);
    void InsertBefore (ListElement<T> const*, T const&);
};
