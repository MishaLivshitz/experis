#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */

/**
 * @brief
 * complexity
 * @...
 * @return 0 on success, otherwise error code
 */  
int Sort(void* _elements, size_t _n, size_t _elemSize, int(*_less)(const void*, const void*));

#endif /* __SORT_H__ */
 
