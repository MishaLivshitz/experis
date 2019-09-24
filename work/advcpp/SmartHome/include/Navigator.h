#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Thread.h"
#include "SharedPtr.h"
#include "IEventGiver.h"
#include "IDispatcher.h"
#include "ISearchable.h"

namespace ServerComponents{

    namespace ServerDetails{
        class SystemTerminatorEvent : public advcpp::Event
        {
        public:
            SystemTerminatorEvent(advcpp::EventDetails::Terminator_tag);
        };
    }

    typedef advcpp::SharedPtr<SmartHomeInterfaces::IEventGiver> SPGiver;
    typedef advcpp::SharedPtr<SmartHomeInterfaces::IDispatcher> SPDispatcher;
    typedef advcpp::SharedPtr<SmartHomeInterfaces::ISearchable> SPSearcher;
    typedef advcpp::SharedPtr<advcpp::Thread> SPThread;

class Navigator: private advcpp::Runnable
{

public:
    Navigator(SPGiver a_giver, SPDispatcher a_dispatcher , SPSearcher a_searcher);
    virtual void run();

    void waitForTerminating() const;
private:
   

    SPGiver           m_giver;
    SPDispatcher      m_dispatcher;
    SPSearcher        m_searcher;
    SPThread          m_thread;

};


}//ServerComponents

#endif //NAVIGATOR_H