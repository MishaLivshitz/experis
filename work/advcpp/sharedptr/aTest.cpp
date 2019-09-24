#include "mu_test.h"

#include <string>
#include <iostream>

#include "SharedPtr.h"


class Animal
{
public:
    Animal(std::string const& name): m_name(name) {++count;};
    virtual ~Animal(){--count;};
    static size_t count;

private:
    std::string m_name;
};

class Cat: public Animal
{
public:
    Cat(std::string const& name): Animal(name){ ++catCount;};
    ~Cat(){--catCount;};
    static size_t catCount;
};

size_t Animal::count = 0;
size_t Cat::catCount = 0;


UNIT(constructor)

    ASSERT_EQUAL(Animal::count, 0);
    {
        advcpp::SharedPtr<Animal> c(new Animal("asda"));        
        ASSERT_EQUAL(Animal::count, 1);
        ASSERT_EQUAL(c.counter(), 1);
        {   
            {
                advcpp::SharedPtr<Animal> c1(c);
                ASSERT_EQUAL(c.counter(), 2);
                ASSERT_EQUAL(Animal::count, 1);
            }
            ASSERT_EQUAL(c.counter(), 1);
            ASSERT_EQUAL(Animal::count, 1);

            advcpp::SharedPtr<Animal> c2(c);
            ASSERT_EQUAL(c.counter(), 2);
            ASSERT_EQUAL(Animal::count, 1);
        }
        ASSERT_EQUAL(c.counter(), 1);
        ASSERT_EQUAL(Animal::count, 1);
    }
    ASSERT_EQUAL(Animal::count, 0);
END_UNIT

UNIT(assign)

    ASSERT_EQUAL(Animal::count, 0);
    {
        advcpp::SharedPtr<Animal> n;
        ASSERT_EQUAL(Animal::count, 0);

        advcpp::SharedPtr<Animal> c(new Animal("asda"));        
        ASSERT_EQUAL(Animal::count, 1);
        ASSERT_EQUAL(c.counter(), 1);
        {   
            {
                advcpp::SharedPtr<Animal> c1(c);
                ASSERT_EQUAL(c.counter(), 2);
                ASSERT_EQUAL(Animal::count, 1);

                n = c1;
                ASSERT_EQUAL(Animal::count, 1);
                ASSERT_EQUAL(c.counter(), 3);
            }
            ASSERT_EQUAL(c.counter(), 2);
            ASSERT_EQUAL(Animal::count, 1);

            advcpp::SharedPtr<Animal> c2(c);
            ASSERT_EQUAL(c.counter(), 3);
            ASSERT_EQUAL(Animal::count, 1);
        }
        ASSERT_EQUAL(c.counter(), 2);
        ASSERT_EQUAL(Animal::count, 1);
    }
    ASSERT_EQUAL(Animal::count, 0);
END_UNIT


UNIT(derived_test_cctor)


    ASSERT_EQUAL(Cat::catCount, 0);
    {
        {
            advcpp::SharedPtr<Cat> cat;
            
            advcpp::SharedPtr<Animal> cat1(new Cat("cat1"));
            ASSERT_EQUAL(Cat::catCount, 1);
            ASSERT_EQUAL(cat1.counter(), 1);
            {
                advcpp::SharedPtr<Animal> anim1(cat1);
                ASSERT_EQUAL(Cat::catCount, 1);
                ASSERT_EQUAL(anim1.counter(), 2);
                ASSERT_EQUAL(cat1.counter(), 2);
            }

            ASSERT_EQUAL(cat1.counter(), 1);
            ASSERT_EQUAL(Cat::catCount, 1);
        }
    }

    ASSERT_EQUAL(Cat::catCount, 0);
END_UNIT


UNIT(derived_test_assign)


    ASSERT_EQUAL(Cat::catCount, 0);
    {
        {
            advcpp::SharedPtr<Cat> cat;
            
            advcpp::SharedPtr<Cat> cat1(new Cat("cat1"));
            
            ASSERT_EQUAL(Cat::catCount, 1);
            ASSERT_EQUAL(cat1.counter(), 1);
            {
                advcpp::SharedPtr<Animal> cat2;
                cat2 = cat1;
                ASSERT_EQUAL(Cat::catCount, 1);
                ASSERT_EQUAL(cat2.counter(), 2);
                ASSERT_EQUAL(cat1.counter(), 2);
            }

            ASSERT_EQUAL(cat1.counter(), 1);
            ASSERT_EQUAL(Cat::catCount, 1);
        }
    }

    ASSERT_EQUAL(Cat::catCount, 0);
END_UNIT

UNIT(null_test)

    advcpp::SharedPtr<Cat> cat(new Cat("DOG"));
    ASSERT_THAT(cat);
    advcpp::SharedPtr<Cat> cat1;
    ASSERT_THAT(!cat1);
      
    ASSERT_THAT(cat);

END_UNIT

TEST_SUITE(shared_pointer_test)

    TEST(constructor)
    TEST(assign)
    TEST(derived_test_cctor)
    TEST(derived_test_assign)
    TEST(null_test)
    

END_SUITE