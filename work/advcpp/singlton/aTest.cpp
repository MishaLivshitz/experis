#include "mu_test.h"
#include "Singleton_v1.h"
#include <string>
#include <iostream>
#include "Thread.h"
#include <unistd.h>


class myRun1: public advcpp::Runnable
{
    virtual void run()
    {
        m_ptr = &advcpp::Singleton_v1::getInstance();
    }

    public:
        advcpp::Singleton_v1* m_ptr;
};

class myRun2: public advcpp::Runnable
{
    virtual void run()
    {
        m_ptr = &advcpp::Singleton_v1::getInstance();
    }

    public:
        advcpp::Singleton_v1* m_ptr;
};


UNIT(singleton)

    myRun1 r1;
    myRun2 r2;

    advcpp::Thread t1(r1);
    advcpp::Thread t2(r2);

    t1.join();
    t2.join();

    ASSERT_EQUAL(r1.m_ptr, r2.m_ptr);
   

END_UNIT

TEST_SUITE(singleton test)



    TEST(singleton)


END_SUITE
