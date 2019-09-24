TARGET = aTest

SOURCES += ../MyException/MyException.cpp 
SOURCES += ../mutex/mutex.cpp ../CondVar/CondVar.cpp ../thread/Thread.cpp 
SOURCES += ../ThreadPoolExecutor/ThreadPoolExecutor.cpp
SOURCES += ../SharedLibUtil/SharedLibUtils.cpp
SOURCES +=  $(wildcard ./SmartHomeInterfaces/*.cpp)
SOURCES +=  $(wildcard ./SmartHomeDevice/*.cpp)
SOURCES +=  $(wildcard ./ServerComponents/*.cpp)
SOURCES +=  $(wildcard ./SmartHomeGeneral/*.cpp)
SOURCES +=  $(wildcard ./Demo/*.cpp)

LDLIBS = -ldl -lpthread

include ../makefile.common

