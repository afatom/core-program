#ifndef _BST_H_
#define _BST_H_
#include "ADTDefs.h"

typedef struct Tree Tree;

typedef enum {
	PRE_ORDER =0,
	IN_ORDER,
	POST_ORDER,
}TreeTraverse;

/*******************************************************************************
*[Description]:Create binary search tree.
*[Input]:Void.
*[Return]:tree pointer.
*[Errors]:None
*******************************************************************************/
Tree*	TreeCreate(void);

/*******************************************************************************
*[Description]:Destroy binary search tree. freeing whole Nodes and tree ptr.
*[Input]:Tree pointer.
*[Return]:Void.
*[Errors]:None
*******************************************************************************/
void	TreeDestroy(Tree* _tree);

/*******************************************************************************
*[Description]:Insert Nodes in sorted Order. 
*[Input]:Tree pointer and Node data.
*[Return]:Err-ok in success case, Err Node Overlap in duplicate data case and
*err not initialized in NULL tree case.
*******************************************************************************/
ADTErr	TreeInsert(Tree* _tree, int _data);

/*******************************************************************************
*[Description]:Search tree for aspecific data. 
*[Input]:Tree pointer and Node data to be searched.
*[Return]:1 = Found. 0 = Not Found.
*******************************************************************************/
int		TreeIsDataFound(Tree* _tree, int _data);
/*******************************************************************************
*[Description]:Tree printing in three modes [in, post and pre order]
*[Input]:Tree pointer and Traverse mode.
*[Return]:Void
*******************************************************************************/
void	TreePrint(Tree* _tree, TreeTraverse _traverseMode);

#endif /*_BST_H_*/
