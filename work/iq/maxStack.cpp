#include <iostream>
#include <stack>
#include <string>

/*g++ -ansi -pedantic -Wall -Werror   maxStack.cpp   -o maxStack -g3*/

class Cat
{
public:
    Cat():m_age(0), m_name("anonymous"){};
    Cat(size_t a_age, std::string const& a_name): m_age(a_age), m_name(a_name) {};

    bool operator<=(Cat const& a_other) const
    {
        return m_age <= a_other.m_age;
    }

    bool operator==(Cat const& a_other) const
    {
        return m_age == a_other.m_age;
    }

    size_t age() const
    {
        return m_age;
    };

    std::string name() const
    {
        return m_name;
    };

    void print(std::ostream& a_os) const
    {
        a_os << name() << ':' << age() << "\n";
    }

private:
    size_t m_age;
    std::string m_name;
};

template <typename T>
class MaxStack
{
    
public:
    void push(T const& a_item)
    {
        
        m_stack.push(a_item);

        if(m_max.empty() || *m_max.top() <= a_item)
        {
            m_max.push(&m_stack.top());
        }
        std::cout << "Max = " << *m_max.top();
    }

    bool pop(T& a_placeHolder)
    {
        if(m_stack.empty())
        {
            return false;
        }

        a_placeHolder =  m_stack.top();
        m_stack.pop();
        
        std::cout << "Max = " << *m_max.top();
        std::cout << "Popping = " << a_placeHolder;
        if(a_placeHolder == *m_max.top())
        {
            m_max.pop();
        }


        return true;
    }

    bool max(T& a_placeHolder)
    {
        if(m_max.empty())
        {
            return false;
        }

        a_placeHolder = *m_max.top();

        return true;
    }

private:

    std::stack<T> m_stack;
    std::stack<T const*> m_max;

};


void operator <<(std::ostream& _os,Cat const& a_cat)
{
    a_cat.print(_os);
}


int main()
{
    
    Cat c1(3,"Boris");
    Cat c2(7,"Idan");
    Cat c3(2,"Muhammad");
    Cat c4(4,"Mirit");
    Cat c5(10,"Moshe");
    Cat c6(10,"Mishe");

    MaxStack<Cat> s;

    s.push(c1);
    s.push(c2);
    s.push(c3);
    s.push(c5);
    s.push(c6);
    s.push(c4);

    Cat temp;
    s.pop(temp);
    s.pop(temp);

    Cat maxi;
    s.max(maxi);
    s.pop(temp);
    s.pop(temp);
    s.pop(temp);
    s.pop(temp);
 

    return 0;
}