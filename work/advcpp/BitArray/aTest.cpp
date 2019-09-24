#include "mu_test.h"
#include "BitSetBase.h"
#include "BitSet.h"


UNIT(bitSetBase)
    size_t size = 80;

    advcpp::BitSetBase b(size);
    advcpp::BitSetBase a(b);
    advcpp::BitSetBase c(size);

    c = a;

    TRACER << c << '\n';

    a.set(8);
    a.set(2);
    a.set(67);
    a.set(0);
    //a.clear(0);

    TRACER << a << '\n';
    ASSERT_EQUAL_INT(a.count(),3);
    a.clear(0);
    ASSERT_EQUAL_INT(a.count(),2);

    c.set(5);
    TRACER << c << '\n';

    c &= a;

    TRACER << a << '\n';
    TRACER << c << '\n';

    ASSERT_THAT(c[5] == 0);
    ASSERT_THAT(a[0] == c[0]);

END_UNIT

UNIT(bitSet)

    advcpp::BitSet<40> a;
    advcpp::BitSet<40> c;
    advcpp::BitSet<30> b;

    a.set(8);
    a.set(2);
    a.set(27);

    c&=a;
    

    ASSERT_THAT(a[8] == 1);
    ASSERT_THAT(a[9] == 0);
    ASSERT_THAT(c[8] == 0);
    ASSERT_THAT(c[9] == 0);

END_UNIT

UNIT(str_ctor)

     advcpp::BitSet<40> a("10101000");

     ASSERT_THAT(a[0] == 1);
     ASSERT_THAT(a[2] == 1);
     ASSERT_THAT(a[4] == 1);


END_UNIT

UNIT(any_all_none_test)

    size_t size = 30;
    advcpp::BitSetBase b(size);
    advcpp::BitSetBase c(size);

    for(size_t i = 0; i < size; ++i)
    {
        b.set(i);
    }

    TRACER << b << '\n';
    TRACER << c << '\n';

    ASSERT_THAT(b.any());
    ASSERT_THAT(b.all());
    ASSERT_THAT(c.none());

    c.set(15);
    ASSERT_THAT(!c.none());
    ASSERT_THAT(!c.all());
    ASSERT_THAT(c.any());

    c|=b;
    TRACER << c << '\n';
    ASSERT_THAT(c.any());
    ASSERT_THAT(c.all());

END_UNIT


TEST_SUITE(Bitarray_test)

TEST(bitSetBase)
TEST(bitSet)
TEST(str_ctor)
TEST(any_all_none_test)


END_SUITE