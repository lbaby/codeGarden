//
//   This file contains the C++ code from Program 13.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_16.cpp
//
void StoragePoolTest (StoragePool& pool, time timeLimit)
{
    UniformRV size (100, 2001);
    UniformRV latency (1, 101);
    PriorityQueue& queue = *new LeftistHeap ();

    RandomNumberGenerator::SetSeed (1);
    for (time t = 0; t < timeLimit; ++t)
    {
	while (!queue.IsEmpty ())
	{
	    Event& event = dynamic_cast<Event&> (
		queue.FindMin ());
	    if (event.Key () > t)
		break;
	    queue.DequeueMin ();
	    pool.Release (event.Value ());
	    delete &event;
	}
	unsigned int const length = size.Sample ();
	void* const address = pool.Acquire (length);
	unsigned int const releaseTime = t + latency.Sample ();
	queue.Enqueue (*new Event (releaseTime, address));
    }
    cout << pool << endl;
    delete &queue;
}
