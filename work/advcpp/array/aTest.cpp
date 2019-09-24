#include "mu_test.h"

#include "Array.h"
#include "utils.h"


UNIT(str_non_const)

    spex::Array<std::string,10> arr;

    arr.fill("hello");
    spex::Array<std::string,10> arr1 = arr;

    spex::Array<std::string,10> arr2;

    arr2 = arr;

    TRACER << arr << '\n';
    TRACER << arr1 << '\n';
    TRACER << arr2 << '\n';

    std::string* itrB = arr2.begin();
    std::string* itrE = arr2.end();

    while(itrB!=itrE)
    {
        ASSERT_EQUAL(*itrB,"hello");
        ++itrB;
    }

END_UNIT

UNIT(str_non_const_pointers)

    spex::Array<std::string*,10> arr;

    std::string s("hello");
    arr.fill(&s);

    spex::Array<std::string*,10> arr1 = arr;
    spex::Array<std::string*,10> arr2;

    arr2 = arr;

    
    TRACER << arr << '\n';
    TRACER << arr1 << '\n';
    TRACER << arr2 << '\n'; 

    std::string** itrB = arr2.begin();
    std::string** itrE = arr2.end();

    while(itrB!=itrE)
    {
        ASSERT_EQUAL(**itrB,"hello");
        ++itrB;
    }

END_UNIT

UNIT(str_const)

    spex::Array<std::string,10> arr;

    arr.fill("hello");
    spex::Array<std::string,10> arr1 = arr;

    spex::Array<std::string,10> arr2;

    arr2 = arr;

    TRACER << arr << '\n';
    TRACER << arr1 << '\n';
    TRACER << arr2 << '\n'; 

    std::string const* itrB = arr2.cbegin();
    std::string const* itrE = arr2.cend();

    while(itrB!=itrE)
    {
        ASSERT_EQUAL(*itrB, "hello");
        ++itrB;
    }

END_UNIT

UNIT(str_const_pointers)

    spex::Array<std::string*,10> arr;

    std::string s("hello");
    arr.fill(&s);

    spex::Array<std::string*,10> arr1 = arr;
    spex::Array<std::string*,10> arr2;

    arr2 = arr;

    TRACER << arr << '\n';
    TRACER << arr1 << '\n';
    TRACER << arr2 << '\n';

    std::string* const* itrB = arr2.cbegin();
    std::string* const* itrE = arr2.cend();

    while(itrB!=itrE)
    {
        ASSERT_EQUAL(**itrB,"hello");
        ++itrB;
    }

END_UNIT

UNIT(reverse_iterator_test)

    spex::Array<std::string*,10> arr;

    std::string s("hello");
    arr.fill(&s);

    arr[9] = new std::string("WHATT?");

    MyReverseIterator::reverse_iterator<std::string*> itrB = arr.rbegin();
    MyReverseIterator::reverse_iterator<std::string*> itrE = arr.rend();

    ASSERT_EQUAL(**itrB,"WHATT?");

    ++itrB;
    for(; itrB!=itrE; ++itrB)
    {
        ASSERT_EQUAL(**itrB,"hello");
    }

    ASSERT_THAT(itrB==itrE);

END_UNIT


UNIT(palindrom)

    int const size = 9;

    spex::Array<int,size> arr;
    utils::fillAscending(arr.begin(),arr.end() - size/2);
    utils::fillDecending(arr.begin() + size/2 - 1, arr.end());

    TRACER << arr << '\n';

    ASSERT_THAT(utils::isPalindrom(arr));

    utils::fillAscending(arr.begin(),arr.end());
    TRACER << arr << '\n';
    ASSERT_THAT(!utils::isPalindrom(arr));


END_UNIT


TEST_SUITE(Array test)

    TEST(str_non_const)
    TEST(str_const)
    TEST(str_non_const_pointers)
    TEST(str_const_pointers)
    TEST(reverse_iterator_test)
    TEST(palindrom)

END_SUITE