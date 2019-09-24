#include <iostream>
#include <bitset>

template <typename T>
T swapBitinPos(T num, T first,T second)
{
    T mask = ((T)1) << first;
    T mask2 = ((T)1) << second;

    if((num&mask && !(num&mask2)) || (!(num&mask) && num&mask2))
    {
        num^=mask;
        num^=mask2;
    }

    return num;

}

template <typename T>
T mirror(T _num)
{
    T first = 0;
    T second = sizeof(T)*8 - 1;

    while(first<second)
    {
        _num = swapBitinPos<T>(_num,first,second);
        ++first;
        --second;
    }

    return _num;
}

typedef unsigned int Uint;
typedef unsigned char Uchar;
typedef unsigned long Ulong;

#include <sys/inotify.h>
#include <unistd.h>

int main()
{
    std::bitset<sizeof(Uint)*8> x(swapBitinPos<Uint>(361,2,5));
    std::bitset<sizeof(Uint)*8> y(mirror<Uint>(5));
    std::cout << x << '\n';
    std::cout << y << '\n';
    
    std::bitset<sizeof(Uchar)*8> x1(swapBitinPos<Uchar>(250,2,5));
    std::bitset<sizeof(Uchar)*8> y1(mirror<Uchar>(15));
    std::cout << x1 << '\n';
    std::cout << y1 << '\n';

    std::bitset<sizeof(Ulong)*8> x2(swapBitinPos<Ulong>(361,2,5));
    std::bitset<sizeof(Ulong)*8> y2(mirror<Ulong>(15));
    std::cout << x2 << '\n';
    std::cout << y2 << '\n';

    /* int fd = inotify_init();
    
    char buf[2048] = {0};
    while(true)
    {
        inotify_add_watch(fd,"myDir",IN_CREATE); 
        read(fd, buf, 2048);
        std::cout<< ((struct inotify_event*)buf)->name << '\n';
        std::cout<< ((struct inotify_event*)buf)->wd << '\n';
        std::cout<< ((struct inotify_event*)buf)->cookie << '\n';
        std::cout<< ((struct inotify_event*)buf)->len << '\n';
        std::cout<< ((struct inotify_event*)buf)->mask << '\n';
    } */
    
}