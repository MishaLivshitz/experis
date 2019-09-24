#ifndef BOOKS_CATALOG_H
#define BOOKS_CATALOG_H

#include <string>
#include <set>
#include <map>
#include <sstream>
#include "Book.h"
#include "Publisher.h"
#include "Author.h"
#include "MyException.h"

class ISBNSearcher;
class WordSearcher;

class BooksCatalog
{
public:
    typedef std::map<std::string, Book*> BookById_t;
    typedef std::map<std::string, std::set<Book*> > BooksByWord_t;

public:
    BooksCatalog();
    ~BooksCatalog();
    //TODO : cctor and assingmet operator
 
    BookById_t const& booksById();
    BooksByWord_t const& booksByWord();

    void add(Book*);
    void insertByName(Book* _b);

    ISBNSearcher getIsbnSearcher() const;
    WordSearcher getWordSearcher() const;

private:
    void  destroyBooks();

private:
    BookById_t m_bookById;
    BooksByWord_t m_bookByWord;
};

inline BooksCatalog::BookById_t const& BooksCatalog::booksById()
{
    return m_bookById;
}
inline BooksCatalog::BooksByWord_t const& BooksCatalog::booksByWord()
{
    return m_bookByWord;
}

inline void BooksCatalog::add(Book* _b)
{
    if(m_bookById.find(_b->id()) == m_bookById.end())
    {
        m_bookById[_b->id()] = _b;
    }

    insertByName(_b);
}


inline std::ostream& operator<< (std::ostream& _os, Book const& _b)
{ 
    _b.print(_os);
    return _os;
}

inline std::ostream& operator<< (std::ostream& _os, std::set<Book*> const& _bSet)
{ 
    std::set<Book*>::const_iterator itrB = _bSet.begin();
    std::set<Book*>::const_iterator itrE = _bSet.end();

    while(itrB!=itrE)
    {
        (*itrB)->print(_os);
       _os << std::endl;
       ++itrB;
    }
    return _os;
}

#endif