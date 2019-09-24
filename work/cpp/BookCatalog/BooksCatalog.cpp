#include "BooksCatalog.h"
#include <algorithm>
#include "ISBNSearcher.h"
#include "WordSearcher.h"


BooksCatalog::BooksCatalog()
: m_bookById()
, m_bookByWord()
{

}

BooksCatalog::~BooksCatalog()
{
    destroyBooks();
}

void BooksCatalog::destroyBooks()
{
    BookById_t::iterator itB = m_bookById.begin();
    BookById_t::iterator itE = m_bookById.end();

    while(itB!=itE)
    {
        delete itB->second;
        ++itB;
    }
}

void BooksCatalog::insertByName(Book* _b)
{

    Title const& t= _b->title();
    size_t const size = t.title().size();

    for(size_t i =0 ;i< size ;++i)
    {
        m_bookByWord[t.title()[i]].insert(_b);
    }
   
    
}

ISBNSearcher BooksCatalog::getIsbnSearcher() const
{
    ISBNSearcher isbnSearcher(m_bookById);
    return isbnSearcher;
}

WordSearcher BooksCatalog::getWordSearcher() const
{
    WordSearcher wordSearcher(m_bookByWord);
    return wordSearcher;
}