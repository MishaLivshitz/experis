#include "mu_test.h"

#include <iostream>
#include "sortedList.h"
#include "isSorted.h"

const size_t RANGE = 1000;


UNIT(add_elements)

    SortedList<int> list;
    const size_t size = 20;

    for(size_t i = 0 ; i<size; i++)
    {
        list.insert(std::rand() % RANGE);
    }


    TRACER << list << '\n';

    //TRACER << list[4] << '\n';

    list.pop_back();
    
    list.erase(list.begin(2));

    list.erase(list.begin(2), list.begin(7));

    TRACER << list << '\n';

    ASSERT_THAT(isSorted<SortedList<int> >(list));


END_UNIT



TEST_SUITE(Sorted vector test)

    TEST(add_elements)

END_SUITE



