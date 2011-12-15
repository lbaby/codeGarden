//
//   This file contains the C++ code from Program 10.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_22.cpp
//
void ReadDictionary (SearchTree& dictionary)
{
    std::string key;
    std::string value;

    ifstream file ("dict.txt");
    while (file >> key >> value, !file.eof ())
	dictionary.Insert (*new Association (
	    *new String (key), *new String (value)));
}

void TranslateText (SearchTree& dictionary)
{
    std::string word;

    while (cin >> word, !cin.eof ())
    {
	Object& obj = dictionary.Find (
	    Association (*new String (word)));
	if (obj.IsNull ())
	    cout << word << "?" << endl;
	else
	{
	    Association& assoc = dynamic_cast<Association&> (obj);
	    cout << assoc.Value () << endl;
	}
    }
}
