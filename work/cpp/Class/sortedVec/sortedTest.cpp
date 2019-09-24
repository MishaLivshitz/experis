#include "mu_test.h"

#include "sortedVec.h"

const size_t RANGE = 1000;


UNIT(add_elements)

    SortedVector<int> vec;
    const size_t size = 20;

    for(size_t i = 0 ; i<size; i++)
    {
        vec.insert(std::rand() % RANGE);
    }

    TRACER << vec[2] << '\n';

    TRACER << vec << '\n';

    vec.pop_back();

    vec.erase(vec.begin()+2);

    vec.erase(vec.begin()+2,vec.begin()+7);

    TRACER << vec << '\n';


END_UNIT



TEST_SUITE(Sorted vector test)

    TEST(add_elements)

END_SUITE



