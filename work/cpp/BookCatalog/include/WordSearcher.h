#ifndef WORD_SEARCHER_H
#define WORD_SEARCHER_H

#include <string>
#include "BooksCatalog.h"

class WordSearcher
{

friend class BooksCatalog;

private:
    WordSearcher(BooksCatalog::BooksByWord_t const& _books);

public:
    std::set<Book*>const& findBookByWord(std::string const& _word) const;

private:
    BooksCatalog::BooksByWord_t const& m_books;
};


#endif