#include "list.h"
#include "person.h"

static Person* FindInsertPlace(Person* _tempHead,int _key)
{
	while(NULL!=_tempHead->m_next)
		{
		
			if(_tempHead->m_next->m_id >= _key)
			{
				return _tempHead;
			}

			_tempHead = _tempHead->m_next;
		}
	return _tempHead;
}

Person* ListInsertHead(Person* _head, Person* _p)
{
	if(NULL == _p)
	{
		return _head;
	}

	if(NULL == _head)
	{
		return _p;
	}
	
	_p->m_next = _head;
	return _p;
}

Person* ListRemoveHead(Person* _head, Person** _item)
{
	if(NULL == _head)
	{	
		*_item = NULL;
		return NULL;
	}
	
	if(NULL==_item)
	{
		return _head;
	}

	*_item = _head;
	_head=_head->m_next;

	return _head;
}

Person* ListInsertByKey(Person* _head,int _key, Person* _p)
{
	bool isInserted = FALSE;
	Person* place = NULL;
	
	if(NULL == _p)
	{
		return _head;
	}

	if(NULL==_head)
	{
		return _p;
	}
	
	if(_head->m_id>_key)
	{
		return ListInsertHead(_head,_p);
	}
	
	place = FindInsertPlace(_head, _key);

	if(place->m_next!=NULL)
	{
		place->m_next =  ListInsertHead(place->m_next,_p);
	}

	else
	{
		place->m_next = _p;
	}

	return _head;
}

Person* ListInsertByKeyRec(Person* _head,int _key, Person* _p)
{

	if(NULL == _p)
	{
		return _head;
	}

	if(_head==NULL)
	{
		return _p;
	}

	if(_head->m_id <= _key)
	{
		_head->m_next = ListInsertByKeyRec(_head->m_next,_key, _p);
		return _head;
	}

	else
	{
		_head = ListInsertHead(_head,_p);
		return _head;
	}
}


Person* ListRemoveByKey(Person* _head,int _key, Person** _p)
{
	Person* place;
	
	if(NULL == _p)
	{
		return _head;
	}
	
	if(_head==NULL)
	{
		*_p=NULL;
		return NULL;
	}

	if(_head->m_id == _key)
	{
		return ListRemoveHead(_head,_p);
	}

	place = FindInsertPlace(_head,_key);
	if(place->m_next!=NULL && place->m_next->m_id==_key )
	{
		place->m_next = ListRemoveHead(place->m_next,_p);
		return _head;
	}
	
	*_p=NULL;
	return _head;
}

Person* ListRemoveByKeyRec(Person* _head,int _key, Person** _p)
{
	
	if(NULL == _p)
	{
		return _head;
	}

	if(_head==NULL)
	{
		*_p=NULL;
		return _head;
	}
	
	if(_head->m_id != _key)
	{
		_head->m_next = ListRemoveByKeyRec(_head->m_next,_key,_p);
	}	

	else
	{
		return ListRemoveHead(_head,_p);
	}
}

void PrintList(Person* _head)
{
	while(_head!=NULL)
	{
		printPersons(_head,1);
		_head=_head->m_next;
	}
}
