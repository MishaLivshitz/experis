#ifndef ISBN_SEARCHER_H
#define ISBN_SEARCHER_H

#include "Book.h"
#include <string>
#include "BooksCatalog.h"

class ISBNSearcher
{

friend class BooksCatalog;

private:
    ISBNSearcher(BooksCatalog::BookById_t const& _books);

public:
    Book* findBookById(std::string const& _id) const;

private:
    BooksCatalog::BookById_t const& m_books;
};


#endif