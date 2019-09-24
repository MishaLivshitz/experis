#include "mu_test.h"
#include "sortedVec.h"
#include "common.h"
#include "Vector.h"

const size_t RANGE = 1000;

UNIT(inherit_test)

    SortedVector<int> vec;
    Vector<int> vec1;

    ASSERT_THAT(vec.type()== "SortedVector");
    ASSERT_THAT(vec1.type()== "Vector");

END_UNIT

UNIT(cast_test)
    Vector<int>* vec;
    SortedVector<int> sVec;
    SortedVector<int>* psVec;

    vec = new SortedVector<int>;

    ASSERT_THAT((isPtrOf<Vector<int>,SortedVector<int> >(vec)));
    ASSERT_THAT(false == (isPtrOf<Vector<int>, Vector<int> >(vec)));

    ASSERT_THAT((tryCast<SortedVector<int>,Vector<int> >(vec)));
    ASSERT_THAT(0 == (tryCast<Vector<int>,SortedVector<int> >(&sVec)));

    psVec = tryCast<SortedVector<int>,Vector<int> >(vec);
    if(psVec)
    {
        delete psVec;
    }
    else
    {
        delete vec;
    }

END_UNIT

UNIT(delete_test)
    Vector<int>* vec;
    Vector<int>* vec1;
    SortedVector<int>* psVec;

    vec = new SortedVector<int>;
    vec1 = new Vector<int>;

    psVec = tryCast<SortedVector<int>,Vector<int> >(vec);
    if(psVec)
    {
        delete psVec;
    }
    else
    {
        delete vec;
    }

    psVec = tryCast<SortedVector<int>,Vector<int> >(vec1);

    if(psVec)
    {
        delete psVec;
    }
    else
    {
        delete vec1;
    }

END_UNIT


UNIT(add_elements)


    Vector<int> myVec;
    Vector<int> myVec2;
    SortedVector<int> vec;

    const size_t size = 20;
    const int intSize = 20;
    int num;

    for(size_t i = 0 ; i<size; ++i)
    {
        num = std::rand() % RANGE;
        vec.insert(num);
        myVec.push_back(num);
    }

    for(int i = intSize ; i>0; --i)
    {
         myVec2.push_back(i);
    }

    vec.erase(vec.cbegin());
    TRACER << vec << '\n';
    TRACER << myVec << '\n';
    TRACER << myVec2 << '\n';

    ASSERT_THAT(isSorted<int>(vec));
    ASSERT_THAT(isSorted<int>(myVec2));
    ASSERT_THAT(!isSorted<int>(myVec));


END_UNIT

TEST_SUITE(Sorted vector test)

    TEST(add_elements)
    TEST(inherit_test)
    TEST(cast_test)
    TEST(delete_test)

END_SUITE



