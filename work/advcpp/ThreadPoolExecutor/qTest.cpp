#include "mu_test.h"
#include "ThreadPoolExecutor.h"
#include <unistd.h>


class sum: public advcpp::Runnable
{
public:
    sum(int a_from, int a_to) :m_from(a_from), m_to(a_to){};

    virtual void run()
    {
        for(int i = m_from; i <= m_to; ++i)
        {
            m_res+=i;
        }
    };

    int result() const { return m_res;};

private:
    int m_res;
    int m_from;
    int m_to;
};


UNIT(create)

    //int const size = 10;
    advcpp::ThreadPoolExecutor t(300);

    advcpp::SharedPtr<sum> p(new sum(0, 5));
    advcpp::SharedPtr<sum> p2(new sum(20, 24));
 
    t.submit(p);
    t.submit(p2);
    t.addWorkers(3);
    ASSERT_EQUAL(t.amount(), 303);
    t.removeWorkers(3);
    ASSERT_EQUAL(t.amount(), 300);
    t.shutDown();

    ASSERT_EQUAL(t.amount(), 0);
    ASSERT_EQUAL(p->result(), 15);
    ASSERT_EQUAL(p2->result(), 110);
    

END_UNIT

TEST_SUITE(Thread pool test)

    TEST(create)


END_SUITE