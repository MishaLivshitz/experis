#ifndef ADT_ITEM_H_
#define ADT_ITEM_H_

/** @file ADTItem.h
 *  @brief typedef of item for use in DS class
 *
 *  @author Alex Katz 28/11/2018
 *
 */

typedef void*	AdtItem;

/* function prototypes */
typedef void (*AdtItemDestroy)	(AdtItem _item);
typedef int  (*AdtItemAction)	(AdtItem _item, void* _context);
typedef void (*AdtItemPrint)	(const AdtItem _item);
typedef int  (*AdtItemCompare)	(const AdtItem _a, const AdtItem _b);
typedef int  (*AdtItemPredicate)(const AdtItem _item, void* _context);

#endif /* ADT_ITEM_H_ */
