#ifndef VECTOR_DEQUEUE_ACTIVATOR_H
#define VECTOR_DEQUEUE_ACTIVATOR_H


#include <vector>
#include "WaitableQueue.h"
#include "Runnable.h"

template <typename T>
class VectorDequeueActivator: public advcpp::Runnable
{

public:
    VectorDequeueActivator(advcpp::WaitableQueue<T>& a_queue, int _size = 0);
    void run();
    bool status() const;
    std::vector<T>& getVec();

private:

    advcpp::WaitableQueue<T>& m_queue;
    T m_lastRemoved;
    T m_lastRemovedNeg;
    int m_numOfItems;
    bool m_status;
    std::vector<T> m_vecRef;
};

template <typename T>
bool VectorDequeueActivator<T>::status() const
{
    return m_status;
}

template <typename T>
VectorDequeueActivator<T>::VectorDequeueActivator(advcpp::WaitableQueue<T>& a_queue, int a_size)
: m_queue(a_queue)
, m_lastRemoved(0)
, m_lastRemovedNeg(-1)
, m_numOfItems(a_size)
, m_status(true)
{

}

template <typename T>
std::vector<T>& VectorDequeueActivator<T>::getVec()
{
    return m_vecRef;
}

template <typename T>
void VectorDequeueActivator<T>::run()
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
        
        m_vecRef.push_back(temp);
    }
}

#endif