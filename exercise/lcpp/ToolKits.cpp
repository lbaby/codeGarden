#include <ToolKits.h>
#include <HashTable.h>
#include <Association.h>
#include <Wrapper.h>
#include <StackAsLinkedList.h>
#include <Event.h>
#include <RandomVariable.h>
#include <InfixVisitor.h>

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>


void CountWords (HashTable& table)
{

   using namespace std;
    std::string word; 
    while (cin >> word, !cin.eof ())
    {
    	Association a   (*new String (word));
	Object& obj =
	    table.Find (a);
	if (obj.IsNull ())
	    table.Insert (*new Association (
		*new String (word), *new Counter (1)));
	else
	{
	    Association& assoc =
		dynamic_cast<Association&> (obj);
	    Counter& i =
		dynamic_cast<Counter&> (assoc.Value ());
	    ++i;
	}
    }
    cout << table << endl;
}


void RPNCalculator (Stack& stack)
{
	using namespace std;
    char c;
    while (cin >> c, !cin.eof ())
    {
	if (std::isdigit (c))
	    stack.Push (*new Int (c - '0'));
	else if (c == '+')
	{
	    Int& arg2 = dynamic_cast<Int&> (stack.Pop ());
	    Int& arg1 = dynamic_cast<Int&> (stack.Pop ());
	    stack.Push (*new Int (arg1 + arg2));
	    delete &arg1;
	    delete &arg2;
	}
	else if (c == '*')
	{
	    Int& arg2 = dynamic_cast<Int&> (stack.Pop ());
	    Int& arg1 = dynamic_cast<Int&> (stack.Pop ());
	    stack.Push (*new Int (arg1 * arg2));
	    delete &arg1;
	    delete &arg2;
	}
	else if (c == '=')
	{
	    Int& arg = dynamic_cast<Int&> (stack.Pop ());
	    cout << arg << endl;
	    delete &arg;
	}
    }
}



void PostfixToInfix ()
{
	using namespace std;
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



void ReadDictionary (SearchTree& dictionary)
{
	using namespace std;
    int key;
    std::string value;

    ifstream file ("dict.txt");
    while (file >> key >> value, !file.eof ())
	dictionary.Insert (*new Association (
	    *new Int (key), *new String (value)));
}

void TranslateText (SearchTree& dictionary)
{
	using namespace std;
    int  word;

    while (cin >> word, !cin.eof ())
    {
	Object& obj = dictionary.Find (
	   *new Int  (word) );
	if (obj.IsNull ())
	    cout << word << "?" << endl;
	else
	{
	    Association& assoc = dynamic_cast<Association&> (obj);
	    cout << assoc.Value () << endl;
	}
    }
}



void Simulation (PriorityQueue& eventList, doub_time doub_timeLimit)
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
	if (t > doub_timeLimit)
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




