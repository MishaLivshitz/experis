#ifndef DEQUEUE_ACTIVATOR_H
#define DEQUEUE_ACTIVATOR_H

#include "WaitableQueue.h"
#include "Runnable.h"

template <typename T>
class DequeueActivator: public advcpp::Runnable
{

public:
    DequeueActivator(advcpp::WaitableQueue<T>& a_queue, int _size = 0);
    void run();
    bool status() const;

private:

    int m_numOfItems;
    advcpp::WaitableQueue<T>& m_queue;
    bool m_status;
    
};

template <typename T>
bool DequeueActivator<T>::status() const
{
    return m_status;
}

template <typename T>
DequeueActivator<T>::DequeueActivator(advcpp::WaitableQueue<T>& a_queue, int a_size)
: m_numOfItems(a_size)
, m_queue(a_queue)
, m_status(true)
{

}

template <typename T>
void DequeueActivator<T>::run()
{
    for(int i = 0; i < m_numOfItems; ++i)
    {
        T temp;
        m_queue.dequeue(temp);
        if(temp != i)
        {
            m_status = false;
            return;
        }
    }
}

#endif