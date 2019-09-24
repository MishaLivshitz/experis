#ifndef THREAD_POOL_EXECUTOR_H
#define THREAD_POOL_EXECUTOR_H

#include "WaitableQueue.h"
#include "Runnable.h"
#include "Thread.h"
#include "vector"
#include "SharedPtr.h"
#include "AtomicVal.h"
#include <algorithm>


namespace advcpp{


class ThreadPoolExecutor;
namespace imp_details
{

class ThreadPoolRunnable: public Runnable
{

public:    

    ThreadPoolRunnable(ThreadPoolExecutor& m_tPool) :m_tPool(m_tPool){};
    virtual void run();

private:
    ThreadPoolExecutor& m_tPool;
};

} // imp_details

class ThreadPoolExecutor
{
public:
    ThreadPoolExecutor(size_t a_numOfThreads);
    ~ThreadPoolExecutor();
    void submit(SharedPtr<Runnable>const&  a_task);
    void addWorkers(size_t a_amount);
    void removeWorkers(size_t a_amount);
    void shutDown();
    size_t amount() const;
    friend class imp_details::ThreadPoolRunnable;

private:
    class Poison : public Runnable
    {
    public:
        virtual void run() {
            
        };
    };

    class Cleaner : public Runnable
    {
    public:
        Cleaner(ThreadPoolExecutor& a_tPool, pthread_t a_tId) :m_tPool(a_tPool), m_tId(a_tId) {};
        virtual void run() 
        {
            m_tPool.removeThread(m_tId);
        };

    private:
        ThreadPoolExecutor& m_tPool;
        pthread_t m_tId;
    };

    class RemoveCountPredicate
    {
    public:
        RemoveCountPredicate(int& a_removeCount)
        :m_removeCountRef(a_removeCount)
        {}

        bool operator()(){ return m_removeCountRef > 0;}
    private:
        int& m_removeCountRef;
    };

private:
    class Cleaner_tag{};
    ThreadPoolExecutor(Cleaner_tag);
    void removeThread(pthread_t a_tId);
    static void makeJoin(SharedPtr<Thread>& a_var);
    SharedPtr<Runnable> getTask();
    void cleanerSubmit(SharedPtr<Runnable>const&  a_task);

private:
    WaitableQueue<SharedPtr<Runnable> > m_queue;
    std::vector<SharedPtr<Thread> >     m_threads;
    imp_details::ThreadPoolRunnable     m_myRunnable;
    ThreadPoolExecutor*                 m_cleaner;
    mutable Mutex                       m_mtx;
    CondVar                             m_cond;
    int                                 m_removeCount;
    
};



} //advcpp





#endif // THREAD_POOL_EXECUTOR_H