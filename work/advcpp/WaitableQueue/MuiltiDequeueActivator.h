#ifndef MULTI_DEQUEUE_ACTIVATOR_H
#define MULTI_DEQUEUE_ACTIVATOR_H

#include "WaitableQueue.h"
#include "Runnable.h"

template <typename T>
class MultiDequeueActivator: public advcpp::Runnable
{

public:
    MultiDequeueActivator(advcpp::WaitableQueue<T>& a_queue, int _size = 0);
    void run();
    bool status() const;

private:

    advcpp::WaitableQueue<T>& m_queue;
    T m_lastRemoved;
    T m_lastRemovedNeg;
    int m_numOfItems;
    bool m_status;
    
};

template <typename T>
bool MultiDequeueActivator<T>::status() const
{
    return m_status;
}

template <typename T>
MultiDequeueActivator<T>::MultiDequeueActivator(advcpp::WaitableQueue<T>& a_queue, int a_size)
: m_queue(a_queue)
, m_lastRemoved(0)
, m_lastRemovedNeg(-1)
, m_numOfItems(a_size)
, m_status(true)
{

}

template <typename T>
void MultiDequeueActivator<T>::run()
{
    T temp;
    for(int i = 0; i < m_numOfItems; ++i)
    {
        m_queue.dequeue(temp);

        if(temp >= 0)
        {
            if(m_lastRemoved > temp)
            {
                m_status = false;
                return;
            
            }

            m_lastRemoved = temp;
        }
        else
        {
            if(m_lastRemovedNeg < temp)
            {
                m_status = false;
                return;
            }

            m_lastRemovedNeg = temp;
        }
    }
}

#endif