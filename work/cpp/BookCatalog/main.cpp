#include <iostream>
#include "BooksCatalog.h"
#include "Loader.h"
#include "ISBNSearcher.h"
#include "WordSearcher.h"
#include "TextProvider.h"

inline void printMenu()
{
    std::cout << "[1. Search by ISBN]" << std::endl;
    std::cout << "[2. Search by Word]" << std::endl;
    std::cout << "[0. Quit]" << std::endl;
}

int main()
{
    char option = '1';
    std::string str;
    BooksCatalog bookCatalog;
    EntityMap<Author> authors;
    EntityMap<Publisher> publisher;
    TextProvider tProvider("./BookCatalogFiles/books-42.txt");

    try 
    {
        Loader tLoad;
        tLoad.load(&tProvider, bookCatalog, publisher, authors);
    }
    catch(MyException e)
    {
        std::cout << e.what()<< std::endl;
        return 0;
    }

    while(true)
    {   
        printMenu();
        std::cout << "Insert your choice: ";
        std::cin >> option;

        switch(option)
        {
            case '1':
            std::cout << "Insert ID: ";
            std::cin >> str;
                try{
                    ISBNSearcher const& searcher = bookCatalog.getIsbnSearcher();
                    std::cout << "\n\n";
                    searcher.findBookById(str)->print(std::cout);
                    std::cout << "\n\n";
                }
                catch(MyException e)
                {
                    std::cout << e.what()<< std::endl;
                }
                break;
            case '2':
                 std::cout << "Insert search word: ";
                 std::cin >> str;
                try{
                    WordSearcher const& searcher = bookCatalog.getWordSearcher();
                    std::cout << "\n\n";
                    std::cout << searcher.findBookByWord(str);
                    std::cout << "\n\n";
                }
                catch(MyException e)
                {
                    std::cout << e.what()<< std::endl;
                }
                break;
            case '0':
                std::cout << "Quiting..." << std::endl;
                return 0;

            default:
                std::cout << "There is no such option" << std::endl;
                break;
        }
    }

}