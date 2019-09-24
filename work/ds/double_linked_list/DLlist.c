#include "DLlist.h"
#include "allocator.h"

typedef struct node
{
	int m_data;
	struct node* m_next;
	struct node* m_prev;
}Node;


struct list{
	int magicNum;
	Node m_head;
	Node m_tail;
	MemPool_t* m_pool;
};

static Node* CreateNode(List* _list,int _data)
{
	Node* node = NULL;

	if(NULL == (node = (Node*)MyMalloc(_list->m_pool)))
	{
		return NULL;
	}
		
	node->m_data=_data;
	node->m_next=NULL;
	node->m_prev=NULL;

	return node;	
}

static void DestroyNode(List* _list,Node* node)
{
	MyFree(_list->m_pool,node);
}

List* ListCreate(size_t _numOfNodes)
{
	List* list = NULL;

	if(NULL == (list = (List*)malloc(sizeof(List))))
	{
		return NULL;
	}

	list->m_pool = CreatePool(sizeof(Node),_numOfNodes);

	if(NULL == list->m_pool)
	{
		return NULL;
	}
	
	list->m_head.m_prev = NULL;
	list->m_head.m_next = &(list->m_tail);
	list->m_tail.m_next = NULL;
	list->m_tail.m_prev = &(list->m_head);
	list->magicNum = MAGIC_NUM_ACTIVE;

	return list;
}

void ListDestroy(List* _list)
{
	if(NULL!=_list && _list->magicNum == MAGIC_NUM_ACTIVE)
	{
		while(!ListIsEmpty(_list))
		{
			ListPopHead(_list,NULL);
		}

		_list->magicNum = MAGIC_NUM_INACTIVE;
		free(_list->m_pool);
		free(_list);
		_list->m_pool = NULL;
	}
	
	return;
}

ADTErr ListPushHead(List* _list, int _data)
{
	Node* node = NULL;

	if(NULL == _list || _list->magicNum != MAGIC_NUM_ACTIVE)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(NULL == (node = CreateNode(_list,_data)))
	{
		return ERR_ALLOCATION_FAILED;
	}

	node->m_prev = _list->m_head.m_next->m_prev;
	node->m_next = _list->m_head.m_next;
	_list->m_head.m_next->m_prev = node;
	_list->m_head.m_next = node;

	return ERR_OK;
}

ADTErr ListPopHead(List* _list, int* _data)
{
	
	Node* removedNode = NULL; 
	
	if(NULL == _list || _list->magicNum != MAGIC_NUM_ACTIVE)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(ListIsEmpty(_list))
	{
		return ERR_EMPTY;
	}
	
	removedNode = _list->m_head.m_next;
	_list->m_head.m_next = removedNode->m_next;
	removedNode->m_next->m_prev = removedNode->m_prev;
	if(NULL != _data)
	{
		*_data = removedNode->m_data;
	}

	DestroyNode(_list,removedNode);
	
	return ERR_OK;
}


ADTErr ListPushTail(List* _list, int _data)
{
	Node* node = NULL;
	List tempList;

	if(NULL == _list || _list->magicNum != MAGIC_NUM_ACTIVE)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(NULL == (node = CreateNode(_list,_data)))
	{
		return ERR_ALLOCATION_FAILED;
	}

	tempList = *_list;
	tempList.m_head = *tempList.m_tail.m_prev;		
	ListPushHead(&tempList,_data);
	_list->m_tail.m_prev->m_prev->m_next = _list->m_tail.m_prev;

	return ERR_OK;
}

ADTErr ListPopTail(List* _list, int* _data)
{

	List tempList;
	
	if(NULL == _list || _list->magicNum != MAGIC_NUM_ACTIVE)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(ListIsEmpty(_list))
	{
		return ERR_EMPTY;
	}
	
	tempList = *_list;
	tempList.m_head = *tempList.m_tail.m_prev->m_prev;
	ListPopHead(&tempList, _data);	
	_list->m_tail.m_prev->m_next = &_list->m_tail;

	return ERR_OK;

}

bool ListIsEmpty(List* _list)
{
	
	if(NULL == _list || _list->magicNum != MAGIC_NUM_ACTIVE)
	{
		return TRUE;
	}

	return _list->m_head.m_next == &(_list->m_tail);

}


size_t ListCountItems(List* _list)
{
	Node* tempNode = NULL;
	size_t counter=0;


	if(NULL == _list || _list->magicNum != MAGIC_NUM_ACTIVE)
	{
		return 0;
	}

	tempNode = &(_list->m_head);
	while(tempNode->m_next != &(_list->m_tail))
	{
		counter++;
		tempNode=tempNode->m_next;
	}

	return counter;
}


void ListPrint(List* _list)
{
	Node* tempNode = NULL;
	
	if(NULL == _list || _list->magicNum != MAGIC_NUM_ACTIVE)
	{
		return;
	}

	if(ListIsEmpty(_list))
	{
		puts("Empty list");
		return;
	}
	
	puts("->");
	tempNode = &(_list->m_head);
	while(tempNode->m_next != &(_list->m_tail))
	{
		printf("%d ",tempNode->m_next->m_data);
		tempNode=tempNode->m_next;
	}

	putchar('\n');
	puts("<-");
	tempNode = &(_list->m_tail);
	while(tempNode->m_prev != &(_list->m_head))
	{
		printf("%d ",tempNode->m_prev->m_data);
		tempNode=tempNode->m_prev;
	}

	putchar('\n');
}
