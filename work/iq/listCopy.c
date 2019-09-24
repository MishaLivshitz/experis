#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{   
    struct Node* m_next;
    struct Node* m_m8;
    int m_val;
}Node;


Node* createNode(int _val)
{
    Node* newNode = malloc(sizeof(Node));
    
    if(!newNode)
    {
        return NULL;
    }

    newNode->m_m8 = NULL;
    newNode->m_next = NULL;
    newNode->m_val = _val;

    return newNode;
}

Node* pushHead(Node* _head, int _val)
{
    Node* newNode = createNode(_val);

    if(!newNode)
    {
        return NULL;
    }

    if(_head == NULL)
    {
        _head = newNode;    
    }
    else
    {
        newNode->m_next = _head;
        _head = newNode;
    }
    
    return _head;
}

Node* findNode(Node* _head, int _index)
{
    while(_head!=NULL && _index > 0)
    {
        _head = _head->m_next;
        --_index;
    }

    return _head;
}

int setm8(Node* _head, size_t _fromIndx,size_t _toIndex)
{

    Node* from = NULL;
    Node* to = NULL;

    from = findNode(_head,_fromIndx);
    to = findNode(_head,_toIndex);
    
    if(!from || !to)
    {
        return -1;
    }

    from->m_m8 = to;
    return 0;
}

void printList(Node* _head)
{
    while(_head!=NULL)
    {
        printf("[Val=%d",_head->m_val);
        if(_head->m_m8)
        {
            printf(",m8=%d]",_head->m_m8->m_val);
        }
        else
        {
           printf("]");
        }
        
        _head = _head->m_next;
    }

    printf("\n");

}

typedef unsigned int Uint;
typedef unsigned char Uchar;
typedef unsigned long Ulong;

Uint swapBitinPos(Uint num, Uint first,Uint second)
{
    Uint mask = 1 << first;
    Uint mask2 = 1 << second;

    if((num&mask && !(num&mask2)) || (!(num&mask) && num&mask2))
    {
        num^=mask;
        num^=mask2;
    }

    return num;

}

Uint mirror(Uint _num)
{
    Uint first = 0;
    Uint second = sizeof(Uint)*8 - 1;

    while(first<second)
    {
        _num = swapBitinPos(_num,first,second);
        ++first;
        --second;
    }

    return _num;
}

int main()
{
   printf("%u\n",swapBitinPos(361,2,5));
   printf("%u\n",mirror(5));

    return 0;
}