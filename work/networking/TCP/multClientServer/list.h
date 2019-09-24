#ifndef LINKED_LIST_H
#define LINKED_LIST_H
/** @file list.h
 *  @brief Linked List contanier - double-linked list 
 *
 *  @author Alex Katz 12.09.2018 - new format and cleanup
 * 	@date modified	  05.05.2019 - abrised syllabus
 *
 *  @bug No known bugs.
 */

#include "ADTItem.h"
#include "stddef.h"		/* size_t */

typedef struct List List;

typedef enum List_Result {
	 LIST_SUCCESS				/**< operation OK */
	,LIST_NOT_INITIALIZED		/**< List is not initialized */
	,LIST_INVALID_ARGUMENT		/**< invalid argument passed */
	,LIST_ALLOCATION_FAILED		/**< memory allocation error */	
	,LIST_UNDERFLOW				/**< List underflow	*/
} List_Result;


/**
 * @brief Create a List ADT container for managing a set of integers
 * @return Created List or NULL on error
 *
 */
List*	List_Create(void);

/**
 * @brief Destroy previously created List container
 * @param _list:  List ADT to be destroyed
 * 		  _destroyer: the function to be called for each destroyed item
 */
void	List_Destroy(List* _list, AdtItemDestroy _destroyer);

/**
 * @brief Add an item to the List container at the head / tail
 * @param[in] _list: the container
 * @param[in] _item:   item to add to the container
 * @returns result code
 * @retval LIST_SUCCESS
 * @retval LIST_NOT_INITIALIZED
 * @retval LIST_ALLOCATION_FAILED
 */
List_Result	List_PushHead(List* _list, AdtItem _item);
List_Result	List_PushTail(List* _list, AdtItem _item);

/**
 * @brief Remove an item from the head/tail of the list
 * @param[in] _list: the container
 * @param[in] _pItem: item value that was removed
 * @returns result code
 * @retval LIST_SUCCESS on success
 * @retval LIST_NOT_INITIALIZED
 * @retval LIST_INVALID_ARGUMENT
 */
List_Result	List_PopHead(List* _list, AdtItem *_pItem);
List_Result	List_PopTail(List* _list, AdtItem *_pItem);

/**
 * @brief Retrieve the current size of List container - O(n)
 * @param[in] _list: List ADT
 * @returns number of items in the container, or -1 if not initialized
 */
int		List_Size(const List* _list);

/**
 * @brief Check if there are items in Vector container
 * @param[in] _vector: Vector container
 * @returns non-zero value if Vector does not have any items.
 */
int		List_IsEmpty(const List* _list);

#ifdef DEBUG
/**
 * @brief Printout to stdout the contents of the container
 * @param[in] _list: List container
 * @param[in] _direction: forward or reverse traversal
 */

typedef enum 
{	
	LIST_DIR_FORWARD		= 1,
	LIST_DIR_BACKWARD		=-1
} e_ListDir;
void	List_Print(const List* _list, e_ListDir _direction, AdtItemPrint _pIPF);
#endif /* DEBUG */

#endif /* LINKED_LIST_H */
