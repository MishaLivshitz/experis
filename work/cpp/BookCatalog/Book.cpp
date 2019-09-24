#include "Book.h"


// Book::Book()
// {}

Book::Book(std::string _isbn, Title _title, size_t _year, Author* _author, Publisher* _publisher)
: m_isbn(_isbn)
, m_title(_title)
, m_year(_year)
, m_author(_author)
, m_publisher(_publisher)
{

}