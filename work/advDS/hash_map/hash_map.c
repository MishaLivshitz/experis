#include "hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ACTIVE_MAGIC_NUM 0xdefdef
#define LOAD_FACOTR 1.3

#define IS_VALID(H)			((H)&&(H)->m_magicNum == ACTIVE_MAGIC_NUM)

#define TABLE(H)			((H)->m_table)
#define KEY(H,I)			((&TABLE(H)[(I)])->m_key)
#define VALUE(H,I)			((&TABLE(H)[(I)])->m_val)
#define STATE(H,I)			((&TABLE(H)[(I)])->m_state)

#define COLLISION_HANDLER(I,S) (((I)+1) % (S))
#define AVG_COLL(AVG,INS,COLL)  (((AVG) * (INS) + (COLL)) / ((INS) + 1))

typedef enum
{
	 FREE = 0
	,IN_USE
	,DIRTY
	
}pState;

typedef struct Pair
{
	void* m_key;
	void* m_val;
	pState m_state;
	
}Pair;

struct HashMap
{
	int m_magicNum;
	Pair* m_table;
	HashFunction m_hashFunc;
	KeyEqualityFunction m_equalFunc;
	size_t m_maxCollisions;
	size_t m_numOfInserts;
	size_t m_capacity;
	size_t m_size;
	float m_averageCollisions;
};

static int isPrime(size_t num){

	int i;
	double root = sqrt(num);
	
	for(i=num-1;i>=root;i--)
	{
		if (num%i==0)
		{
			return 0;
		}
	}
	return 1;
}

static size_t FindNextPrime(size_t num){

	while(!isPrime(num))
	{
		num++;
	}
	
	return num;
}

static Map_Result insertAction(HashMap* _map, const void* _key, const void* _value,size_t _insertIndex, size_t _collisions)
{
	if(-1 == _collisions)
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	
	if(_collisions > _map->m_maxCollisions)
	{
		_map->m_maxCollisions = _collisions;
	}
	
	KEY(_map,_insertIndex) = (void*)_key;
	VALUE(_map,_insertIndex) = (void*)_value;
	STATE(_map,_insertIndex) = IN_USE;
	
	_map->m_size++;
	_map->m_averageCollisions = AVG_COLL(_map->m_averageCollisions,_map->m_numOfInserts,_collisions);
	_map->m_numOfInserts++;
	
	return MAP_SUCCESS;
}

static int FindNextPlace(HashMap* _map, size_t* _insertIndex, const void* _key)
{
	size_t collisionCounter = 0;
	
	while(IN_USE == STATE(_map,*_insertIndex))
	{
		if(_map->m_equalFunc(KEY(_map,*_insertIndex),_key))
		{
			return -1;
		}
		
		collisionCounter++;
		*_insertIndex = COLLISION_HANDLER(*_insertIndex,_map->m_capacity);
	}
	
	return collisionCounter;
}

HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, KeyEqualityFunction _keysEqualFunc)
{
	HashMap* map;
	
	if(!(_capacity && _hashFunc && _keysEqualFunc))
	{
		return NULL;
	}
	
	map = (HashMap*)calloc(1,sizeof(HashMap));
	
	if(!map)
	{
		return NULL;
	}
	
	_capacity = FindNextPrime(_capacity*LOAD_FACOTR);
	
	TABLE(map) = (Pair*)calloc(_capacity,sizeof(Pair));
	
	if(!TABLE(map))
	{
		free(map);
		return NULL;
	}
	
	map->m_hashFunc = _hashFunc;
	map->m_equalFunc = _keysEqualFunc;
	map->m_capacity = _capacity;
	map->m_magicNum = ACTIVE_MAGIC_NUM;
	
	return map;
}

void HashMap_Destroy(HashMap* _map, void (*_keyDestroy)(void*), void (*_valDestroy)(void*))
{
	size_t i;
	
	if(!IS_VALID(_map))
	{
		return;
	}
	
	for (i=0;_map->m_size > 0;i++)
	{
		if(IN_USE==STATE(_map,i))
		{
			STATE(_map,i) = DIRTY;
			
			if(_keyDestroy) 
			{
				_keyDestroy(KEY(_map,i));
				
			}
			
			if( _valDestroy)
			{
				_valDestroy(VALUE(_map,i));	
			}
			
			_map->m_size--;
		}
	}
	_map->m_magicNum = -1;
	free(TABLE(_map));
	free(_map);
}

Map_Result HashMap_Rehash(HashMap *_map, size_t _newCapacity)
{

	HashMap* newMap;
	size_t i;
	int mapSize;
	size_t insertIndex;
	int collisionCounter;
	
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}

	newMap = HashMap_Create(_newCapacity,_map->m_hashFunc,_map->m_equalFunc);
	
	if(!newMap)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	for(i=0,mapSize = _map->m_size; mapSize > 0 ;i++)
	{
		if(IN_USE == STATE(_map,i))
		{
			insertIndex = newMap->m_hashFunc(KEY(_map,i));
			insertIndex %= newMap->m_capacity;
			collisionCounter = FindNextPlace(newMap,&insertIndex,KEY(_map,i));
			insertAction(newMap,KEY(_map,i),VALUE(_map,i),insertIndex,collisionCounter);
			mapSize--;
		}
	}
	
	free(TABLE(_map));
	*_map=*newMap;
	free(newMap);
	
	return MAP_SUCCESS;
}

Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value)
{
	size_t insertIndex;
	size_t collisionCounter;
	
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(_map->m_size == _map->m_capacity)
	{
		return MAP_OVERFLOW_ERROR;
	}
	
	if(NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	insertIndex = _map->m_hashFunc(_key);
	insertIndex %= _map->m_capacity;
	collisionCounter = FindNextPlace(_map,&insertIndex,_key);
	
	return insertAction(_map,_key,_value,insertIndex,collisionCounter);
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void* *_pKey, void* *_pValue)
{
	size_t collisionCounter;
	size_t index;
	
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = _map->m_hashFunc(_searchKey);
	index %= _map->m_capacity;
	
	for(collisionCounter=0;collisionCounter<=_map->m_maxCollisions && FREE != STATE(_map,index); collisionCounter++)
	{
		if(IN_USE == STATE(_map,index) && _map->m_equalFunc(KEY(_map,index),_searchKey))
		{
			*_pValue = VALUE(_map,index);
			*_pKey = KEY(_map,index);
			STATE(_map,index) = DIRTY;
			_map->m_size--;
			return MAP_SUCCESS;
		}
		
		index = COLLISION_HANDLER(index,_map->m_capacity);
		
	}
	
	return MAP_KEY_NOT_FOUND_ERROR;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	size_t collisionCounter;
	size_t index;
	
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = _map->m_hashFunc(_searchKey);
	index %= _map->m_capacity;
	
	for(collisionCounter=0;collisionCounter<=_map->m_maxCollisions && FREE != STATE(_map,index);collisionCounter++)
	{
	
		if(IN_USE == STATE(_map,index) && _map->m_equalFunc(KEY(_map,index),_searchKey))
		{
			*_pValue = VALUE(_map,index);
			return MAP_SUCCESS;
		}
	
		index = COLLISION_HANDLER(index,_map->m_capacity);
	}
	
	return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMap_Size(const HashMap* _map)
{
	if(!IS_VALID(_map))
	{
		return 0;
	}
	
	return _map->m_size;
}

size_t HashMap_Capacity(const HashMap* _map)
{
	if(!IS_VALID(_map))
	{
		return 0;
	}
	
	return _map->m_capacity;
}

Map_Result HashMap_Statistics(const HashMap* _map, size_t *_maxCollisionsEver, float *_averageCollisions)
{
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	*_maxCollisionsEver = _map->m_maxCollisions;
	*_averageCollisions = _map->m_averageCollisions;
	
	return MAP_SUCCESS;
}

size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	size_t i,actionsPerforemd;
	size_t size;
	if(!IS_VALID(_map) || !_action)
	{
		return 0;
	}
	
	for(i=0,actionsPerforemd=0,size =_map->m_size; size>0 ;i++)
	{
		if(IN_USE==STATE(_map,i))
		{
			if(!_action(KEY(_map,i),VALUE(_map,i),_context))
			{
				break;
			}
			actionsPerforemd++;
			size--;
		}
	}
	
	return actionsPerforemd;
}
