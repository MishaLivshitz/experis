#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <iostream>
#include <vector>

class TextProcessor
{

public:
    typedef std::vector<std::string> Vector;

    TextProcessor();
    virtual ~TextProcessor();
    virtual void process(std::string const&);
    
    size_t numLinesProcessed() const;
    void display(std::ostream&) const;


protected:
    Vector m_vec;

};


#endif