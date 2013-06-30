#ifndef _PUTTINGVISITOR_H_
#define _PUTTINGVISITOR_H_

class PuttingVisitor : public Visitor
{
    std::ostream& stream;
    bool comma;
public:
    PuttingVisitor (std::ostream& s) : stream (s), comma (false)
	{}
    void Visit (Object& object)
    {
	if (comma)
	    stream << ", ";
	stream << object;
	comma = true;
    }
    virtual ~ PuttingVisitor()
    {}
};


#endif
