#include "Loader.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

Loader::Loader()
{
}

void Loader::load(Provider* _provider,BooksCatalog& _bc, EntityMap<Publisher>& _publishers, EntityMap<Author>& _authors)
{
    std::map<int, std::string>* lineMap;
    while((lineMap = _provider->provide()) != 0)
    {
        _publishers.add((*lineMap)[PUBLISHER]);
        _authors.add((*lineMap)[AUTHOR]);
        
        Book* book = new Book((*lineMap)[ISBN],
                        Title((*lineMap)[TITLE]),
                        atoi((*lineMap)[YEAR].c_str()),
                        _authors.get((*lineMap)[AUTHOR]),
                        _publishers.get((*lineMap)[PUBLISHER]));

        _bc.add(book);
        lineMap->clear();
    }
    delete lineMap;
}