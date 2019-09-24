#include "mu_test.h"
#include "HashMap.h"


UNIT(create)

try
{
    HashMap h(10);

    
    for(size_t i = 0; i<10; ++i)
    {
        h.add(i*20);
    }

    ASSERT_EQUAL(h.find(20),20);

    h.print();
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

END_UNIT




TEST_SUITE(Hash map test)

    TEST(create)

END_SUITE



