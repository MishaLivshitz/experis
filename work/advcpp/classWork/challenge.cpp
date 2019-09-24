
#include <iostream>

class B
{
    public:
        virtual int fx(){ return 10;};
        virtual int fz(){ return 20;};
};


typedef int(*PF)();

int main()
{
    B* p = new B();
    // int* vptr = (int*)p;

    p -=9762;

    std::cout << ((PF)&p[2])() << '\n';
    
    


}