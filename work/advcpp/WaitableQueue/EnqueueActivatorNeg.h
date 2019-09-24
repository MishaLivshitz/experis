#ifndef ENQUEUE_ACTIVATOR_NEG_H
#define ENQUEUE_ACTIVATOR_NEG_H

#include "WaitableQueue.h"
#include "Runnable.h"

template <typename T>
class EnqueueActivatorNeg: public advcpp::Runnable
{

public:
    EnqueueActivatorNeg(advcpp::WaitableQueue<T>& a_queue, size_t _size = 0);
    void run();

private:

    int m_numOfItems;
    advcpp::WaitableQueue<T>& m_queue;
    
};

template <typename T>
EnqueueActivatorNeg<T>::EnqueueActivatorNeg(advcpp::WaitableQueue<T>& a_queue, size_t a_size)
: m_numOfItems(a_size)
, m_queue(a_queue)
{

}

template <typename T>
void EnqueueActivatorNeg<T>::run()
{
    for(int i = 1; i <= m_numOfItems; ++i)
    {
        m_queue.enqueue(-i);
    }
}

#endif