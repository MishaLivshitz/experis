#include "Animal.h"
#include "SharedLibUtil.h"


typedef Animal* (*PF)();
int main()
{
    try
    {
        PF makeDog;
        PF makeCat;

        advcpp::SharedLibUtil so("./libAnim.so");

        makeDog = (PF)so.getPtr("makeDog");
        Animal* dog = makeDog();
        
        makeCat = (PF)so.getPtr("makeCat");
        Animal* cat = makeCat();

        dog->setName("Doberman");
        dog->makeNoise();

        cat->setName("Kitty");
        cat->makeNoise();

    }
    catch(MyException& e)
    {
        std::cout << e.what();
    }
    return 0;
}