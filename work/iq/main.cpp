#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include<queue>

/* template<typename T>
struct LessThan{
    bool operator()(T const& a, T const& b){
        return a < b;
    }
};

template<typename Iterator, typename Comparator>
Iterator minElement(Iterator first, Iterator last, Comparator cmp){
    if(first == last){
        return last;
    }
    Iterator min = first;
    ++first;
    while(first != last){
        if( cmp(*first, *min) ) {
            min = first;
        }
        ++first;
    }
    return min;
}

template<typename T, typename Iterator>
std::pair<Iterator, Iterator> minMaxElements(Iterator first, Iterator last){
    minMaxElements(first, last, LessThan<T>());
}

template<typename Iterator, typename Comparator>
std::pair<Iterator,Iterator> minMaxElements(Iterator first, Iterator last, Comparator cmp){


    if(first == last){
        return std::make_pair(last,last);
    }

    Iterator next = first;
    ++next;

    if(next == last)
    {
        return std::make_pair(first,first);
    }

    std::pair<Iterator,Iterator> res;

    if( cmp(*first, *next)) 
    {
        res.first = first;
        res.second = next;
    }
    else
    {
       res.first = next;
       res.second = first;
    }

    first+=2;
    next+=2;
    
    std::pair<Iterator,Iterator> temp;

    while(first != last && next != last){

        if(cmp(*first, *next)) 
        {
            temp.first = first;
            temp.second = next;
        }
        else
        {
           temp.first = next;
           temp.second = first;
        }
        
        if(cmp(*temp.first, *res.first))
        {
            res.first = temp.first;
        }

        if(cmp(*res.second, *temp.second))
        {
            res.second = temp.second;
        }

        first+=2;
        next+=2;
    }

    if(first!=last)
    {
        if(cmp(*first,*res.first))
        {
            res.first = first;
        }
        else if(cmp(*res.second,*first))
        {
            res.second = first;
        }
    }

    return res;
}

template<typename  T, typename Iterator>
Iterator minElement(Iterator first, Iterator last){
    return minElement(first, last, LessThan<T>());
}

template<typename  T, typename Iterator>
Iterator maxElement(Iterator first, Iterator last){
   return minElement(first, last, std::greater<T>());
}



template <typename T, typename Iterator>
Iterator firstNoneUnique(Iterator first, Iterator last)
{
    typename std::map<T,int> map;
    typename std::map<T, int>::iterator b;

    Iterator candidate = last;
    int i = 0;

    while(first!=last)
    {
        b = map.find(*first);
        if(b != map.end())
        {
            if(candidate != last)
            {
                if(map[*candidate] > b->second)
                {
                    candidate = first;
                }
            }
            else
            {
               candidate = first;
            }
        }
        else
        {
            map[*first] = i;
        }

        ++i;
        ++first;
    }

    return candidate;
}

template <typename Iterator, typename Comparator>
Iterator SecondMax(Iterator first, Iterator last, Comparator cmp)
{
    if(first = last)
    {
        return last;
    }

    --last;

    Iterator max1 = first;
    Iterator max2 = last;
    Iterator innerMin = *max1 > *max2 ? max2: max1;

    ++first;
    --last;

    while(first <= last)
    {
        if(cmp(*innerMin, *first))
        {
            if(cmp(*max1, *max2)
            {
                if(cmp(*max1,*first))
                {
                    max1 = first;
                    innerMin = *max1 > *max2 ? max2: max1;
                }
            }
            else
            {
                if(cmp(*max1,*first))
                {
                    max1 = first;
                    innerMin = *max1 > *max2 ? max2: max1;
                }
            }
            
        }
    } 
}

bool isPalindrom(std::string& str,int begin,int end)
{
    while(begin<end)
    {
        if(str[begin] != str[end])
        {
            return false;
        }

        ++begin;
        --end;
    }

    return true;
}

std::string findSubPalindrom(std::string& str)
{

    const size_t size = str.size();

    for(size_t i = 0; i < size; ++i)
    {
        for(size_t j = size; j > i; --j)
        {
            if(isPalindrom(str,i,j))
            {
                return std::string(str, i, j-i+1);
            }
        }
    }
    
    return "";
} 
 */


void initMap(int const* a_arr, std::map<int, std::queue<int> >& a_map, size_t a_size)
{
    for(size_t i = 0; i < a_size; ++i)
    {
        a_map[a_arr[i]].push(i);
    }
}

int findInMap(std::map<int, std::queue<int> >& a_map, int num)
{
    std::map<int, std::queue<int> >::iterator f = a_map.find(num);

    if(f != a_map.end() && !f->second.empty())
    {
        int num = f->second.front();
        f->second.pop();
        return num;
    }

    return -1;
}

int sumIfEqualTo(int const* arr, size_t size, int num)
{
    if(arr == 0)
    {
        return -1;
    }

    std::map<int, std::queue<int> > myMap;
    initMap(arr, myMap, size);
    int sum = 0;
    for(size_t i = 0; i< size; ++i)
    {
        int index1 = findInMap(myMap,arr[i]);

        if(index1 != -1)
        {
            int index2 = findInMap(myMap, num - arr[i]);
            if(index2 != -1)
            {
                sum+= index1 + index2;
            }
        }
    }

    return sum;
}

int rightGreater(int* a_arr, int n)
{

    if(a_arr==0 || n==0)
    {
        return 0;
    }
    int max = a_arr[n-1];
    int temp = 0;


    for(int i = n-1; i>=0;--i)
    {
        if(a_arr[i] > max)
        {
            temp = a_arr[i];
            a_arr[i] = max;
            max = temp;
        }
        else
        {
            a_arr[i] = max;
        }
    }

    return 1;

}


int main() {
   /*  int n[]={1, 3, 7, 1, 10, 1, 15, 3};
    std::vector<int> v(n, n+ sizeof(n)/ sizeof(n[0]));

    std::pair<std::vector<int>::iterator,std::vector<int>::iterator >  min = minMaxElements<int>(v.begin(), v.end());
    std::cout << *min.first << ' ' << *min.second << std::endl;

    std::cout << *firstNoneUnique<int>(v.begin(),v.end()) << std::endl; */

    /* std::string str = "ABC1771CDTW";
    std::cout << findSubPalindrom(str) << std::endl; */

    int n[]= {5,17,3,9,2,5};
    std::cout << sumIfEqualTo(n, sizeof(n)/sizeof(n[0]) ,1) << std::endl;
    std::cout << rightGreater(n, sizeof(n)/sizeof(n[0])) << '\n';

    for(int i = 0; i < sizeof(n)/sizeof(n[0]) ;++i)
    {
        std::cout << n[i] << ' ';
    }
    
    return 0;
}