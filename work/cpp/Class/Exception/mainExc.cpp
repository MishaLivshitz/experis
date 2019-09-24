#include "RandomFactory.h"
#include <climits>
#include <iostream>

int mul(int a, int b) throw(std::overflow_error)
{   
    if (a*b > 500)
    {
        throw std::overflow_error("integer overflow");
    }

    return a*b;
}

int* f(int _n) throw(std::exception)
{
    RandomFactory rFact;
    int *arr;

    if(_n < 1)
    {
        throw std::invalid_argument("Must be greater then 0");
    }

    arr = new int[_n];
    try{
        for(int i = 0 ; i < _n ;++i)
        {
            const int x = rFact.generateInt(0, INT_MAX);
            arr[i] = mul(x,x);
        }
    }
    catch(std::overflow_error const& e)
    {
        delete[] arr;
        std::cout << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "some exception" << std::endl;
    }

    return arr;
}


int main()
{

    f(500);

}