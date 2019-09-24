#include "WordSearcher.h"


WordSearcher::WordSearcher(BooksCatalog::BooksByWord_t const& _books)
:m_books(_books)
{
   
}

std::set<Book*>const & WordSearcher::findBookByWord(std::string const& _word) const
{
    BooksCatalog::BooksByWord_t::const_iterator itr = m_books.find(_word);
    if(itr == m_books.end())
    {
        throw EXCEPTION(MyException,"Word not found");
    }

    return itr->second;
}