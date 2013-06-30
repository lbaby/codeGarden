//
//   This file contains the C++ code from Program 11.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_22.cpp
//
void Simulation (PriorityQueue& eventList, time timeLimit)
{
    bool serverBusy = false;
    unsigned int numberInQueue = 0;
    ExponentialRV serviceTime (100.);
    ExponentialRV interArrivalTime (100.);

    eventList.Enqueue (*new Event (Event::arrival, 0));
    while (!eventList.IsEmpty ())
    {
	Event& event =
	    dynamic_cast<Event&> (eventList.DequeueMin ());
	Event::Time& t = event.Key ();
	if (t > timeLimit)
	{
	    delete &event;
	    eventList.Purge ();
	    break;
	}
	switch (event.Value ())
	{
	case Event::arrival:
	    if (!serverBusy)
	    {
		serverBusy = true;
		eventList.Enqueue (*new Event (Event::departure,
		    t + serviceTime.Sample ()));
	    }
	    else
		++numberInQueue;
	    eventList.Enqueue (*new Event (Event::arrival,
		t + interArrivalTime.Sample ()));
	    break;
	case Event::departure:
	    if (numberInQueue == 0)
		serverBusy = false;
	    else
	    {
		--numberInQueue;
		eventList.Enqueue (*new Event (Event::departure,
		    t + serviceTime.Sample ()));
	    }
	    break;
	}
	delete &event;
    }
}
