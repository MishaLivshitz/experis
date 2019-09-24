#ifndef LIST_ITR_H__
#define LIST_ITR_H

/** @file list_itr.h
 *  @brief Linked List container - list iterator layer
 *
 *  @author Alex Katz 12.09.2018 - new format and cleanup
 * 	@date modified	  05.05.2019 - abridged syllabus
 *
 *  @bug No known bugs.
 */

#include "list.h"

typedef struct ListItr* ListItr;

/** 
 * @brief Get itertator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 */
ListItr ListItr_Begin(const List* _list);

/** 
 * @brief Get itertator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 */
ListItr ListItr_End(const List* _list);

/** 
 * @brief retruns none zero if _a and _b iterators refer to same node
 * @warning might be implemented as a macro
 */
int ListItr_Equals(const ListItr _a, const ListItr _b);

/** 
 * @brief Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 */
ListItr ListItr_Next(ListItr _itr);

/** 
 * @brief Get itertator to the previous element
 * @warning if _itr is begin iterator it will be returned
 */
ListItr ListItr_Prev(ListItr _itr);

/** 
 * @brief Get data from the list node the iterator is pointing to
 *
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing to the end
 */
AdtItem ListItr_Get(ListItr _itr);

/** 
 * @brief Set data at the node where the iterator is pointing at
 * @return the data from the node to be changed
 */
AdtItem ListItr_Set(ListItr _itr, AdtItem _element);

/** 
 * @brief Inserts a new node BEFORE node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItr_Insert(ListItr _itr, AdtItem _element);

/** 
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data
 */
AdtItem ListItr_Remove(ListItr _itr);

/** 
 * @brief Finds the first element in a range satsifying a predicate
 * @details find the element for which the predicate returns a non-zero value
 *  in the half open range [begin..end)
 *
 * @param _begin : start search from here
 * @param _end : end search here - not included
 * @param _predicate : Predicate function
 * @param _context : context to be passed to the predicate
 * @return an iterator pointing to the first node with data found or to _end if not
 */
ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, AdtItemPredicate _predicate, void* _context);

/** 
 * @brief execute an action for all elements in a half open range
 * @details call -action for each element in the range [begin..end)
 * iteration will stop if Action function returns 0 for an element
 *
 * @param _begin: A list iterator to start operations from
 * @param _end : A list iterator to end operations on
 * @param _Action : user provided action function
 * @param _context : Parameters for the function
 * @return number of items _action was performed
 */
size_t ListItr_ForEach(ListItr _begin, ListItr _end, AdtItemAction _action, void* _context);

#endif /* LIST_ITR_H */
