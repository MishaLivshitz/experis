#ifndef BOOK_H
#define BOOK_H

#include "Author.h"
#include "Publisher.h"
#include <map>
#include <iostream>
#include "Title.h"

class Book
{
public:
    Book();
    Book(std::string _isbn, Title _title, size_t _year, Author* _author, Publisher* _publisher);

    std::string const& id() const;
    size_t year() const;
    Author* author() const;
    Publisher* publisher() const;
    Title const& title() const;
    std::ostream& print(std::ostream& _os) const;

private:

    std::string m_isbn;
    Title       m_title;
    size_t      m_year;
    Author*     m_author;
    Publisher*  m_publisher;
};


inline std::string const& Book::id() const
{
    return m_isbn;
}

inline Title const& Book::title() const
{
    return m_title;
}

inline size_t Book::year() const
{
    return m_year;
}

inline Author* Book::author() const
{
    return m_author;
}

inline Publisher* Book::publisher() const
{
    return m_publisher;
}

inline std::ostream& Book::print(std::ostream& _os) const
{
    _os << "ISBN: "         << m_isbn << std::endl;
    m_title.print(_os);
    _os << "Author: "       << m_author->name()  << std::endl;
    _os << "Year: "         << m_year  << std::endl;
    _os << "Publisher: "    << m_publisher->name()  << std::endl;

    return _os;
}

#endif