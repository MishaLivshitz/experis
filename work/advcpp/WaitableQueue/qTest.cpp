#include "mu_test.h"
#include "WaitableQueue.h"
#include "EnqueueActivator.h"
#include "EnqueueActivatorNeg.h"
#include "DequeueActivator.h"
#include "MuiltiDequeueActivator.h"
#include "VectorDequeueActivator.h"
#include "Thread.h"

#include <vector>
#include <algorithm>

template <typename T>
bool isDiffByOne(T const& a_lhs, T const& a_rhs)
{
    return a_lhs + 1 == a_rhs;
}


UNIT(enqueue_1_dequeue_1)

    int const size = 1000000;
    advcpp::WaitableQueue<int> q;
    EnqueueActivator<int> eA(q, size);
    DequeueActivator<int> dA(q, size);
    advcpp::Thread t(eA);
    advcpp::Thread t1(dA);

    t.join();
    t1.join();

    ASSERT_THAT(dA.status());


END_UNIT

UNIT(enqueue_1_dequeue_2)

    int const size = 1000000;
    advcpp::WaitableQueue<int> q;
    EnqueueActivator<int> eA(q, size);
    MultiDequeueActivator<int> mdA(q, size/2);
    MultiDequeueActivator<int> mdA1(q, size/2);
    advcpp::Thread t(eA);
    advcpp::Thread t1(mdA);
    advcpp::Thread t2(mdA1);

    t.join();
    t1.join();
    t2.join();

    ASSERT_THAT(mdA.status() && mdA1.status());


END_UNIT

UNIT(enqueue_2_dequeue_1)

    int const size = 1000000;
    advcpp::WaitableQueue<int> q;
    EnqueueActivator<int> eA(q, size/2);
    EnqueueActivatorNeg<int> eA1(q, size/2);
    MultiDequeueActivator<int> dA(q, size);
    advcpp::Thread t(eA);
    advcpp::Thread t1(eA1);
    advcpp::Thread t2(dA);

    t.join();
    t1.join();
    t2.join();

    ASSERT_THAT(dA.status());


END_UNIT

UNIT(enqueue_2_dequeue_2)

    int const size = 1000000;
    advcpp::WaitableQueue<int> q;
    EnqueueActivator<int> eA(q, size);
    EnqueueActivatorNeg<int> eA1(q, size);
    VectorDequeueActivator<int> vdA(q, size);
    VectorDequeueActivator<int> vdA1(q, size);
    std::vector<int> vec;

    advcpp::Thread t(eA);
    advcpp::Thread t1(eA1);
    advcpp::Thread t2(vdA);
    advcpp::Thread t3(vdA1);

    t.join();
    t1.join();
    t2.join();
    t3.join();

    ASSERT_THAT(vdA.status() && vdA1.status());

    vec.reserve(vdA.getVec().size() + vdA1.getVec().size());
    vec.insert(vec.end(),vdA.getVec().begin(),vdA.getVec().end());
    vec.insert(vec.end(),vdA1.getVec().begin(),vdA1.getVec().end());

    std::sort(vec.begin(),vec.end());
    ASSERT_THAT(std::equal(vec.begin(), vec.end() - 1, vec.begin() + 1, isDiffByOne<int>));


END_UNIT


TEST_SUITE(waitable_queue_test)

    TEST(enqueue_1_dequeue_1)
    TEST(enqueue_1_dequeue_2)
    TEST(enqueue_2_dequeue_1)
    TEST(enqueue_2_dequeue_2)

END_SUITE