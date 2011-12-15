

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

#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdexcept>

using  std::domain_error;
using std::invalid_argument ;

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

        friend class LinkedList<T>;
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



//ListElement

template <class T>
ListElement<T>::ListElement (
        T const& _datum, ListElement<T>* _next) :
                datum (_datum), next (_next)
{}

template <class T>
T const& ListElement<T>::Datum () const
{
        return datum;
}

template <class T>
ListElement<T> const* ListElement<T>::Next () const
{
        return next;
}




//LinkedLlist

template <class T>
LinkedList<T>::LinkedList () :
                head (0),
                tail (0)
{}


template <class T>
void LinkedList<T>::Purge ()
{
        while (head != 0) {
                ListElement<T>* const tmp = head;
                head = head->next;
                delete tmp;
        }
        tail = 0;
}

template <class T>
LinkedList<T>::~LinkedList ()
{
        Purge ();
}

template <class T>
ListElement<T> const* LinkedList<T>::Head () const
{
        return head;
}

template <class T>
ListElement<T> const* LinkedList<T>::Tail () const
{
        return tail;
}

template <class T>
bool LinkedList<T>::IsEmpty () const
{
        return head == 0;
}



template <class T>
T const& LinkedList<T>::First () const
{
        if (head == 0)
                throw domain_error ("list is empty");
        return head->datum;
}

template <class T>
T const& LinkedList<T>::Last () const
{
        if (tail == 0)
                throw domain_error ("list is empty");
        return tail->datum;
}



template <class T>
void LinkedList<T>::Prepend (T const& item)
{
        ListElement<T>* const tmp = new ListElement<T> (item, head);
        if (head == 0)
                tail = tmp;
        head = tmp;
}

template <class T>
void LinkedList<T>::Append (T const& item)
{
        ListElement<T>* const tmp = new ListElement<T> (item, 0);
        if (head == 0)
                head = tmp;
        else
                tail->next = tmp;
        tail = tmp;
}

template <class T>
LinkedList<T>::LinkedList (LinkedList<T> const& linkedList) :
                head (0),
                tail (0)
{
        ListElement<T> const* ptr;
        for (ptr = linkedList.head; ptr != 0; ptr = ptr->next)
                Append (ptr->datum);
}

template <class T>
LinkedList<T>& LinkedList<T>::operator = (
        LinkedList<T> const& linkedList)
{
        if (&linkedList != this) {
                Purge ();
                ListElement<T> const* ptr;
                for (ptr = linkedList.head; ptr != 0; ptr = ptr->next)
                        Append (ptr->datum);
        }
        return *this;
}



template <class T>
void LinkedList<T>::Extract (T const& item)
{
        ListElement<T>* ptr = head;
        ListElement<T>* prevPtr = 0;
        while (ptr != 0 && ptr->datum != item) {
                prevPtr = ptr;
                ptr = ptr->next;
        }
        if (ptr == 0)
                throw invalid_argument ("item not found");
        if (ptr == head)
                head = ptr->next;
        else
                prevPtr->next = ptr->next;
        if (ptr == tail)
                tail = prevPtr;
        delete ptr;
}

template <class T>
void LinkedList<T>::InsertAfter (
        ListElement<T> const* arg, T const& item)
{
        ListElement<T>* ptr = const_cast<ListElement<T>*> (arg);
        if (ptr == 0)
                throw invalid_argument ("invalid position");
        ListElement<T>* const tmp =
                new ListElement<T> (item, ptr->next);
        ptr->next = tmp;
        if (tail == ptr)
                tail = tmp;
}

template <class T>
void LinkedList<T>::InsertBefore (
        ListElement<T> const* arg, T const& item)
{
        ListElement<T>* ptr = const_cast<ListElement<T>*> (arg);
        if (ptr == 0)
                throw invalid_argument ("invalid position");
        ListElement<T>* const tmp = new ListElement<T> (item, ptr);
        if (head == ptr)
                head = tmp;
        else {
                ListElement<T>* prevPtr = head;
                while (prevPtr != 0 && prevPtr->next != ptr)
                        prevPtr = prevPtr->next;
                if (prevPtr == 0)
                        throw invalid_argument ("invalid position");
                prevPtr->next = tmp;
        }
}



#endif

