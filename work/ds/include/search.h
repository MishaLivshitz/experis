#include "vector.h"

/*
Implements LinearSearch

params: _vec
		_index: of returned item
		_itemToSearch

return ERR_OK if SUCCESS ERR_NOT_FOUND or ERR_NOT_INITIALIZED or ERR_NULL_POINTER

*/
ADTErr LinearSearch(Vector* _vec,int _itemToSearch, size_t* _index);

/*
Implements LinearSearch

params: _vec
		_index: of returned item
		_itemToSearch
return ERR_OK if SUCCESS ERR_NOT_FOUND or ERR_NOT_INITIALIZED or ERR_NULL_POINTER

*/
ADTErr BinarySearch(Vector* _vec,int _itemToSearch, size_t* _index);
