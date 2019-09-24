#ifndef ENQUEUE_ACTIVATOR_H
#define ENQUEUE_ACTIVATOR_H

#include "WaitableQueue.h"
#include "Runnable.h"

template <typename T>
class EnqueueActivator: public advcpp::Runnable
{

public:
    EnqueueActivator(advcpp::WaitableQueue<T>& a_queue, size_t _size = 0);
    void run();

private:

    int m_numOfItems;
    advcpp::WaitableQueue<T>& m_queue;
    
};

template <typename T>
EnqueueActivator<T>::EnqueueActivator(advcpp::WaitableQueue<T>& a_queue, size_t a_size)
: m_numOfItems(a_size)
, m_queue(a_queue)
{

}

template <typename T>
void EnqueueActivator<T>::run()
{
    for(int i = 0; i < m_numOfItems; ++i)
    {
        m_queue.enqueue(i);
    }
}

#endif