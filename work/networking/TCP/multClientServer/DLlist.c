#include "list.h"
#include "list_itr.h"
#include <stdio.h>
#include <stdlib.h>

#define  MAGIC_NUM_ACTIVE 	0xdefdef
#define  IS_VALID(L)		((L) && (L)->m_magicNum)
#define	 LIST_HEAD(L)		(&(L)->m_head)
#define	 LIST_TAIL(L)		(&(L)->m_tail)

#define  ITR_NODE(I)		((Node*)(I))
#define	 ITR_NEXT(I)		((ListItr)ITR_NODE(I)->m_next)
#define	 ITR_PREV(I)		((ListItr)ITR_NODE(I)->m_prev)
#define  ITR_DATA(I)		(ITR_NODE(I)->m_data)

#define LIST_FIRST(L) (LIST_HEAD(L)->m_next)
#define LIST_LAST(L) (LIST_TAIL(L)->m_prev)

typedef struct Node
{
	struct Node* m_next;
	struct Node* m_prev;
	AdtItem m_data;
	
}Node;


struct List{
	
	int m_magicNum;
	Node m_head;
	Node m_tail;
	
};

static Node* CreateNode(AdtItem _data)
{
	Node* node = NULL;

	if(NULL == (node = (Node*)calloc(1,sizeof(Node))))
	{
		return NULL;
	}
		
	node->m_data=_data;
	
	return node;	
}

static void DestroyNode(Node* _node)
{
	free(_node);
}

List* List_Create(void)
{
	List* list = NULL;

	if(NULL == (list = (List*)malloc(sizeof(List))))
	{
		return NULL;
	}

	LIST_HEAD(list)->m_prev = NULL;
	LIST_FIRST(list) = LIST_TAIL(list);
	LIST_TAIL(list)->m_next = NULL;
	LIST_LAST(list) = LIST_HEAD(list);
	list->m_magicNum = MAGIC_NUM_ACTIVE;

	return list;
}

void List_Destroy(List* _list, AdtItemDestroy _destroyer)
{
	AdtItem item;
		
	if(IS_VALID(_list))
	{	
		while(!List_IsEmpty(_list))
		{
			List_PopHead(_list,&item);	
			if(_destroyer)
			{
				_destroyer(item);
			}
		}
		
		_list->m_magicNum = -1;
		free(_list);
	}
	
	return;
}

static Node* InsertBefore(Node* _curr, Node* _newNode)
{
	_newNode->m_next = _curr;
	_newNode->m_prev = _curr->m_prev;
	_curr->m_prev->m_next = _newNode;
	_curr->m_prev = _newNode;
	
	return _newNode;
}

static Node* DetacheNode(Node* _node)
{
	_node->m_next->m_prev=_node->m_prev;
	_node->m_prev->m_next=_node->m_next;
	
	return _node;
}

List_Result	List_PushHead(List* _list, AdtItem _item)
{
	Node* node = NULL;

	if(!IS_VALID(_list))
	{
		return LIST_NOT_INITIALIZED;
	}
	
	if(NULL == (node = CreateNode(_item)))
	{
		return LIST_ALLOCATION_FAILED;
	}

	InsertBefore(LIST_FIRST(_list),node);

	return LIST_SUCCESS;
}

List_Result	List_PushTail(List* _list, AdtItem _item)
{
	Node* node = NULL;

	if(!IS_VALID(_list))
	{
		return LIST_NOT_INITIALIZED;
	}
	
	if(NULL == (node = CreateNode(_item)))
	{
		return LIST_ALLOCATION_FAILED;
	}

	InsertBefore(LIST_TAIL(_list),node);

	return LIST_SUCCESS;
}

List_Result	List_PopHead(List* _list, AdtItem* _pItem)
{
	
	Node* removedNode = NULL; 
	
	if(!IS_VALID(_list))
	{
		return LIST_NOT_INITIALIZED;
	}

	if(List_IsEmpty(_list))
	{
		return LIST_UNDERFLOW;
	}
	
	if(!_pItem)
	{
		return LIST_INVALID_ARGUMENT;
	}
	
	removedNode = DetacheNode(LIST_FIRST(_list));
	*_pItem = removedNode->m_data;
	
	DestroyNode(removedNode);
	
	return LIST_SUCCESS;
}

List_Result	List_PopTail(List* _list, AdtItem* _pItem)
{

	Node* removedNode = NULL; 
	
	if(!IS_VALID(_list))
	{
		return LIST_NOT_INITIALIZED;
	}

	if(List_IsEmpty(_list))
	{
		return LIST_UNDERFLOW;
	}
	
	if(!_pItem)
	{
		return LIST_INVALID_ARGUMENT;
	}
	
	removedNode = DetacheNode(LIST_LAST(_list));
	*_pItem = removedNode->m_data;
	
	DestroyNode(removedNode);

	return LIST_SUCCESS;
}

int	List_IsEmpty(const List* _list)
{
	
	if(!IS_VALID(_list))
	{
		return 1;
	}

	return LIST_FIRST(_list) == LIST_TAIL(_list);
}

static int CountItem(AdtItem _item, void* _context)
{
	return 1;
}

int	List_Size(const List* _list)
{

	if(!IS_VALID(_list))
	{
		return -1;
	}
	
	return ListItr_ForEach((ListItr)LIST_FIRST(_list),(ListItr)LIST_TAIL(_list),CountItem,NULL);
}

ListItr ListItr_Begin(const List* _list)
{

	if(!IS_VALID(_list))
	{
		return NULL;
	}
	
	return (ListItr)LIST_FIRST(_list);

}

ListItr ListItr_End(const List* _list)
{
	if(!IS_VALID(_list))
	{
		return NULL;
	}
	
	return (ListItr)LIST_TAIL(_list);
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	if(! (_a && _b))
	{
		return 0;
	}
	
	return _a == _b;	
}

ListItr ListItr_Next(ListItr _itr)
{	
	if(!_itr)
	{
		return NULL;
	}

	return ITR_NEXT(_itr) ? ITR_NEXT(_itr): _itr;
}

ListItr ListItr_Prev(ListItr _itr)
{
	if(!_itr)
	{
		return NULL;
	}
	
	return ITR_PREV(_itr) ? ITR_PREV(_itr): _itr;
}

AdtItem ListItr_Get(ListItr _itr)
{
	if(!_itr || !ITR_NEXT(_itr))
	{
		return NULL;
	}
	
	return ITR_DATA(_itr);
}

AdtItem ListItr_Set(ListItr _itr, AdtItem _element)
{
	AdtItem prevData;
	
	if(!_itr)
	{
		return NULL;
	}
	
	prevData = ITR_DATA(_itr);
	ITR_DATA(_itr) = _element;
	
	return prevData;
}

ListItr ListItr_Insert(ListItr _itr, AdtItem _element)
{
	Node* newNode = NULL;
	if(!_itr)
	{
		return NULL;
	}
	
	newNode = CreateNode(_element);
	if(!newNode)
	{
		return NULL;
	}
	
	return (ListItr)InsertBefore(ITR_NODE(_itr),newNode);
}

AdtItem ListItr_Remove(ListItr _itr)
{
	Node* returnedNode;
	AdtItem returnedData;
	
	if(!_itr)
	{
		return NULL;
	}
	
	returnedNode = DetacheNode(ITR_NODE(_itr));
	returnedData = returnedNode->m_data;
	DestroyNode(returnedNode);
	
	return returnedData;
}

ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, AdtItemPredicate _predicate, void* _context)
{
	
	if(!(_begin && _end && _predicate && _context))
	{
		return NULL;
	}
	
	while(!ListItr_Equals(_begin,_end))
	{
		if(_predicate(ITR_DATA(_begin),_context))
		{
			return _begin;
		}
		
		_begin = ListItr_Next(_begin);
	}
	
	return _end;
}

size_t ListItr_ForEach(ListItr _begin, ListItr _end, AdtItemAction _action, void* _context)
{
	int i;
	
	if(!(_begin && _end && _action))
	{
		return 0;
	}
	
	for(i=0; !ListItr_Equals(_begin,_end); i++, _begin = ListItr_Next(_begin))
	{
		if(!_action(ITR_DATA(_begin),_context))
		{	
			return i;
		}
	}
	
	return i;
}
