
#include "mu_test.h"

#include "DeviceConfig.h"
#include <unistd.h>
#include "SystemInitializer.h"
#include "TempEvent.h"
#include "ACController.h"
#include "TempSensor.h"
#include "SoBuilder.h"
#include "MatchesHolder.h"
#include "Location.h"
#include "ConfigurationHandler.h"

advcpp::AtomicVal<size_t> counter;
advcpp::AtomicVal<int> temp;

using::advcpp::SharedPtr;
using::SmartHomeDevice::DeviceConfig;

UNIT(subscriber_search)
    using SmartHomeGeneral::Location;
    using SmartHomeInterfaces::IEventHandler;
    using ServerComponents::MatchesHolder;

    MatchesHolder sm;

    IEventHandler* h1 = reinterpret_cast<IEventHandler*>(42);
    IEventHandler* h2 = reinterpret_cast<IEventHandler*>(43);
    IEventHandler* h3 = reinterpret_cast<IEventHandler*>(0xdeaddef);
    Location r101("r101", 4);
    Location r102("r102", 4);
    Location r42("r42", 32);
    
    sm.receiveSubscription(std::make_pair("t", r101), h1);
    sm.receiveSubscription(std::make_pair("t", r101), h2);
    sm.receiveSubscription(std::make_pair("t", r102), h2);
    sm.receiveSubscription(std::make_pair("c", r101), h3);

    ASSERT_EQUAL(sm.search(std::make_pair("z", r42)), 0);
    ASSERT_EQUAL(sm.search(std::make_pair("z", r101)), 0);
    ASSERT_EQUAL(sm.search(std::make_pair("z", r102)), 0);
    ASSERT_EQUAL(sm.search(std::make_pair("t", r42)), 0);
    MatchesHolder::Consumers const * cp;
    cp = sm.search(std::make_pair("t", r102));
    TRACER << (*cp)[0] << '\n';
    TRACER << (*cp)[0] << " " << (*cp)[1] << " " << (*cp)[2] << '\n';
    ASSERT_EQUAL(cp->size(), 1);

    cp = sm.search(std::make_pair("t", r101));
    ASSERT_NOT_EQUAL(cp, 0);
    TRACER << (*cp)[0] << " " << (*cp)[1] << " " << (*cp)[2] << '\n';
    ASSERT_EQUAL(cp->size(), 2);
    
END_UNIT

UNIT(so_test)
    using ServerComponents::SystemInitializer;
    using advcpp::SharedPtr;
    using ServerComponents::SoBuilder;

    SystemInitializer sys(SharedPtr<SoBuilder> (new SoBuilder));

    
    sleep(30);
    sys.shutDown();

    ASSERT_THAT(true);

END_UNIT

UNIT(devices_holder_test)

    using ServerComponents::SoBuilder;
    using ServerComponents::DevicesHolder;
    using ServerComponents::MatchesHolder;
    using ServerComponents::EventsContainer;
    using advcpp::SharedPtr;

    SharedPtr <MatchesHolder> mh(new MatchesHolder);
    SharedPtr <EventsContainer> es(new EventsContainer);

    std::vector<advcpp::SharedPtr<SmartHomeDevice::DeviceConfig> > m_configs;
    m_configs.push_back(SharedPtr<DeviceConfig>(new  DeviceConfig("111", "Room1",1, "ACController", "config")));
    m_configs.push_back(SharedPtr<DeviceConfig>(new  DeviceConfig("111", "Room1",1, "TempSensor", "config")));

    advcpp::SharedPtr<DevicesHolder> dh(new DevicesHolder);

    SoBuilder sob;

    sob.build(dh, m_configs);

    dh->connectDevices(es, mh);

    ASSERT_THAT(true);

END_UNIT
UNIT(conf_test)
    using ServerComponents::ConfigurationHandler;

    ConfigurationHandler cf("config.txt");

    ASSERT_EQUAL(cf.configs().size(),2);

END_UNIT

UNIT(wrong_file_test)

    using ServerComponents::SystemInitializer;
    using advcpp::SharedPtr;
    using ServerComponents::SoBuilder;

    try
    {
        SystemInitializer sys(SharedPtr<SoBuilder> (new SoBuilder), "jsjs.txt");
        ASSERT_THAT(false);
    }
    catch(MyException& e)
    {
        std::cout << e.what();
        ASSERT_THAT(true);
    }


END_UNIT


TEST_SUITE(Test smartHome)

    TEST(subscriber_search)
    TEST(so_test)
    TEST(devices_holder_test)
    TEST(conf_test)
    TEST(wrong_file_test)


END_SUITE