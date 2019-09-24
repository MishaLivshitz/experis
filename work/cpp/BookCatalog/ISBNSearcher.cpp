#include "ISBNSearcher.h"


ISBNSearcher::ISBNSearcher(BooksCatalog::BookById_t const& _books)
:m_books(_books)
{
   
}

Book* ISBNSearcher::findBookById(std::string const& _id) const
{
    BooksCatalog::BookById_t::const_iterator itr = m_books.find(_id);
    if(itr == m_books.end())
    {
        throw EXCEPTION(MyException,"id not found");
    }

    return itr->second;
}