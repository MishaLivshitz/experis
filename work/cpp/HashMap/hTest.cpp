#include "mu_test.h"
#include "HashMap.h"
#include <climits> 

#include <string>

int hashFunc(std::string _str)
{
    size_t len = _str.length();
    int accumulator = _str[0];

    for(size_t i = 1; i<len; ++i)
    {
        accumulator += _str[i]*pow(2,i);
        accumulator %= INT_MAX;
    }

    return accumulator;
}

UNIT(hash_create)

    HashMap<std::string, std::string, hashFunc> h(6);
    std::string const sArr[6] = {"a","b","c","d","e","f"};

    for(int i = 0; i < 30; ++i)
    {
        h.insert(sArr[i%6],sArr[i%6]);
    }
    
    h.print();
    h.insert("Yechiel","Yechiel");
    h.rehash();
    h.print();


END_UNIT


TEST_SUITE(hash test)

    TEST(hash_create)

END_SUITE
