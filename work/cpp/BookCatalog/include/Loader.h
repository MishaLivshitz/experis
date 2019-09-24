#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <fstream> 
#include "BooksCatalog.h"
#include "EntityMap.h"
#include "Publisher.h"
#include "Author.h"
#include "Provider.h"

class Loader
{

//Exceptions??
public: 
    Loader();
    void load(Provider* _p, BooksCatalog& _bc, EntityMap<Publisher>& _publishers, EntityMap<Author>& _authors);

public:
    enum Headers {ISBN, TITLE, AUTHOR, YEAR, PUBLISHER, LEN};
    static const Headers headers;    
};

#endif