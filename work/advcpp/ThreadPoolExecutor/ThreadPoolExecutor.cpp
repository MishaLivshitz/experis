#include "ThreadPoolExecutor.h"
#include "Thread.h"
#include <algorithm>
#include <unistd.h>

namespace advcpp{


ThreadPoolExecutor::ThreadPoolExecutor(Cleaner_tag)
:m_myRunnable(*this)
,m_cleaner(0)
,m_cond(m_mtx)
{
    addWorkers(1);
}

ThreadPoolExecutor::ThreadPoolExecutor(size_t a_numOfThreads)
:m_myRunnable(*this)
,m_cond(m_mtx)
{
    m_threads.reserve(a_numOfThreads);
    m_cleaner = new ThreadPoolExecutor(Cleaner_tag());
    addWorkers(a_numOfThreads);
}

void ThreadPoolExecutor::makeJoin(SharedPtr<Thread>& a_var)
{
    a_var->join();
}

ThreadPoolExecutor::~ThreadPoolExecutor()
{
    Mutex::MutexUtil m(m_mtx);
    std::for_each(m_threads.rbegin(), m_threads.rend(), makeJoin);

    if(m_cleaner)
    {
        m_cleaner->shutDown();
        delete m_cleaner;
    }
}

void ThreadPoolExecutor::submit(SharedPtr<Runnable>const& a_task)
{
    m_queue.enqueue(a_task);
}

void ThreadPoolExecutor::cleanerSubmit(SharedPtr<Runnable>const&  a_task)
{
    if(m_cleaner)
    {
        m_cleaner->submit(a_task);
    }
    else
    {
        Mutex::MutexUtil m(m_mtx);
        --m_removeCount;
        m_cond.signal();
    }
    
}

SharedPtr<Runnable> ThreadPoolExecutor::getTask()
{
    SharedPtr<Runnable> task;
    m_queue.dequeue(task);
    return task;
}

void ThreadPoolExecutor::addWorkers(size_t a_amount)
{
    Mutex::MutexUtil mtx(m_mtx);
    for(size_t i = 0; i < a_amount; ++i)
    {
        SharedPtr<Thread> sharedPThread(new Thread(m_myRunnable));
        m_threads.push_back(sharedPThread);
    }
}

void ThreadPoolExecutor::removeWorkers(size_t a_amount)
{
    assert(a_amount <= amount());

    Mutex::MutexUtil m(m_mtx);
    m_removeCount = a_amount;
    
    for(size_t i = 0; i < a_amount; ++i)
    {
        advcpp::SharedPtr<Poison> p(new Poison);
        submit(p);
    }

    m_cond.wait(RemoveCountPredicate(m_removeCount));
    
}

void ThreadPoolExecutor::removeThread(pthread_t a_tId)
{
    Mutex::MutexUtil mtx(m_mtx);
    std::vector<SharedPtr<Thread> >::iterator itrB = m_threads.begin();
    std::vector<SharedPtr<Thread> >::iterator itrE = m_threads.end();
    
    while(itrB!=itrE)
    {
        if((**itrB) == a_tId)
        {
            (*itrB)->detach();
            m_threads.erase(itrB);
            --m_removeCount;
            m_cond.signal();   
            break;
        }

        ++itrB;
    }
}

void ThreadPoolExecutor::shutDown()
{
    removeWorkers(amount());
}

size_t ThreadPoolExecutor::amount() const
{
    Mutex::MutexUtil mtx(m_mtx);
    return m_threads.size();
}

void imp_details::ThreadPoolRunnable::run()
{
    while(true)
    {
        SharedPtr<Runnable> task = m_tPool.getTask();
        if(dynamic_cast<ThreadPoolExecutor::Poison*>(&*task))
        {
            advcpp::SharedPtr<ThreadPoolExecutor::Cleaner> c(new ThreadPoolExecutor::Cleaner(m_tPool, pthread_self()));
            m_tPool.cleanerSubmit(c);
            
            break;
        }
        
        try
        {
            task->run();
        }
        catch(...)
        {
            //write to log or something
        }
    }

}



}//advcpp