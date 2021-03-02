#include "bin_tree.h"
#include <stdlib.h>
#include <stdio.h>

#define TREE_VALID 		0xBEEFBEEF
#define TREE_DESTROYED 	0xDEADBEEF
#define TRUE  1
#define FALSE 0
#define ALLOCATION_SUCCESS 1
#define ALLOCATION_FAILURE 0
#define DIFFER 0
#define EQUAL 1

/******************************************************************************/
typedef struct Node {
	struct Node*    m_father;
	struct Node*    m_left;
	struct Node*    m_right;
	void* 	        m_data;
} Node;

struct BSTree {
	size_t			m_magic;
	Node			m_root;
	LessComparator 	m_isLess;
	
};
/*
struct BSTreeItr
{
	Node* m_current;
};*/
/******************************************************************************/

static void DistroyNodes(Node *nodePtr, void (*_destroyer)(void*));
static Node* CreateNode(void* _item);
/*static BSTreeItr FindFirstNode(Node *_root, PredicateFunction _predicate, void *_context);*/
static BSTreeItr FindMaxElement(BSTreeItr _it);
static BSTreeItr GetTheMostLeftChild(BSTreeItr _it);
static BSTreeItr FindMinElement(BSTreeItr _it);
static BSTreeItr GetTheMostRightChild(BSTreeItr _it);
static BSTreeItr FindYoungestFather(BSTreeItr _it);
static void WildFreeNodes(Node *nodePtr);
static void TreePrintInOrder(Node* nodePtr, ActionFunction _action, void* _context);
static void TreePrintPreOrder(Node* nodePtr, ActionFunction _action, void* _context);
static void TreePrintPostOrder(Node* nodePtr, ActionFunction _action, void* _context);
/******************************************************************************/

/** 
 * @brief Create a binary search tree
 * Creates an empty binary search tree with sentinel
 * 
 * @param _less: A comparison function 
 *				that returns true (none zero value) if x < y 
 *				and false (zero) otherwise.
 * @return a pointer to the newly created tree.
 * @retval NULL on failure due to allocation failure or NULL function pointer given
 */
BSTree* BSTreeCreate(LessComparator _less)
{
    BSTree* tree = NULL;
    if(NULL == _less)
    {
        return NULL;
    }

    tree = malloc(sizeof(*tree));
    if(NULL == tree)
    {
        return NULL;
    }

    tree->m_root.m_father = &tree->m_root;
    tree->m_root.m_data = NULL;
    tree->m_root.m_right = &tree->m_root;
    tree->m_root.m_left = NULL;
    tree->m_isLess = _less;
    tree->m_magic = TREE_VALID;
    return tree;
}
/******************************************************************************/
static void DistroyNodes(Node *nodePtr, void (*_destroyer)(void*))
{
    if(NULL == nodePtr)
    {
        return;
    }

    /*Activate _destroyer On elements*/
    DistroyNodes(nodePtr->m_left, _destroyer);
    DistroyNodes(nodePtr->m_right,_destroyer);
    _destroyer(nodePtr->m_data);
    return;
}
/******************************************************************************/
static void WildFreeNodes(Node *nodePtr)
{
    if(NULL == nodePtr)
    {
        return;
    }

    WildFreeNodes(nodePtr->m_left);
    WildFreeNodes(nodePtr->m_right);
	free(nodePtr);
    return;
}
/******************************************************************************/


/******************************************************************************/
void  BSTreeDestroy(BSTree** _tree, void (*_destroyer)(void*))
{
    if(_tree == NULL || *_tree == NULL)
    {
        return;
    }
    /*first set magic to dead beef*/
    (*_tree)->m_magic = TREE_DESTROYED;
    if(NULL == _destroyer)
    {
        WildFreeNodes((*_tree)->m_root.m_left);
    }
    else
    {
        DistroyNodes((*_tree)->m_root.m_left, _destroyer);
    } 
    /*destroy Tree*/
    free(*_tree);
    *_tree = NULL;
    return;
}

/******************************************************************************/
static Node* CreateNode(void* _item)
{
    Node* newNode = NULL;
    newNode = malloc(sizeof(*newNode));
    if(NULL == newNode)
    {
        return NULL;
    }
    newNode->m_data = _item;
    return newNode;
}
/******************************************************************************/
/*
 * @param _tree : A previously created Tree ADT returned via BSTreeCreate
 * @param _item: An item to add to the tree
 * @return iterator pointing to the item added or iterator to end on failure
 * @warning don't allow duplicates
*/
BSTreeItr BSTreeInsert(BSTree* _tree, void* _item)
{
    Node* newNode = NULL;
    Node* starter = NULL;

    if(NULL == _tree || _tree->m_magic != TREE_VALID || NULL == _item)
    {
        return (BSTreeItr)((Node*)_tree->m_root);
    }
    
    if((newNode = CreateNode(_item)) == NULL)
    {
        return (BSTreeItr)((Node *)_tree->m_root);
    }

    starter = _tree->m_root.m_left;

    while(TRUE)
    {
        if(starter->m_left != NULL && _tree->m_isLess(newNode->m_data, starter->m_data))
        {
            starter = starter->m_left;
        }
        else if(starter->m_right != NULL && !_tree->m_isLess(newNode->m_data, starter->m_data))
        {
            starter = starter->m_right;
        }
        
        else if(starter == NULL) /*first insertion*/
        {
            starter = newNode;
            return (BSTreeItr)newNode;
           
        }
        else if(starter->m_right == NULL && !_tree->m_isLess(newNode->m_data, starter->m_data))
        {
            starter->m_right = newNode;
            return (BSTreeItr)newNode;
        }
        else
        {
            return NULL;
        }
    }
    return (BSTreeItr)newNode;
}
/******************************************************************************/
BSTreeItr BSTreeItrBegin(const BSTree *_tree)
{
    Node* runPtr = NULL;
    if (NULL == _tree || _tree->m_magic != TREE_VALID || NULL == _tree->m_root.m_left)
    {
        return NULL;
    }
    runPtr = _tree->m_root.m_left;
    while (runPtr->m_left != NULL)
    {
        runPtr = runPtr->m_left;
    }
    return (BSTreeItr)(runPtr);
}

/******************************************************************************/
BSTreeItr BSTreeItrEnd(const BSTree *_tree)
{
    Node *runPtr = NULL;
    if (NULL == _tree || _tree->m_magic != TREE_VALID || NULL == _tree->m_root.m_left)
    {
        return NULL;
    }
    runPtr = _tree->m_root.m_left;
    while (runPtr->m_right != NULL)
    {
        runPtr = runPtr->m_right;
    }
    return (BSTreeItr)(runPtr);
}
/******************************************************************************/
/** 
 * @brief Compare two iterators
 *
 * @param _a, _b : Iterators to compare
 * @return : 0 if are not the same 
 *           any none zero value if iterators are the same
 */
int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
    return (_a == _b) ? (EQUAL):(DIFFER);
}

/******************************************************************************/
/** 
 * @brief Search the first element for which the given predicate returns 0
 * iterating using in-order manner over elements
 * O(k * n) where O(k) is the time complexity of the predicate
 *
 * @param _tree : A previously created Tree ADT returned via BSTreeCreate
 * @param _predicate : Predicate function
 * @param _params : Predicate parameters
 * @return an iterator pointing to the first data found, to end of tree if not found or NULL on NULL input
 */
/*
BSTreeItr BSTreeFindFirst(const BSTree *_tree, PredicateFunction _predicate, void *_context)
{
    if (NULL == _tree || _tree->m_magic != TREE_VALID || NULL == _tree->m_root.m_left)
    {
        return NULL;
    }

    return FindFirstNode(_tree->m_root.m_left, _predicate, _context);
}
*/
/******************************************************************************/
/*
static BSTreeItr FindFirstNode(Node *_root, PredicateFunction _predicate, void *_context)
{
    if (_root->m_left != NULL)
    {
        BSTreeFindFirst(_root->m_left, _predicate, _context);
    }

    if (__predicate(BSTreeItrGet(_root), _context) == TRUE)
    {
        return (BSTreeItr)(_root);
    }

    if (_root->m_right != NULL)
    {
        BSTreeFindFirst(_root->m_right, _predicate, _context);
    }

    return (BSTreeItr)(_root->m_right);
}*/

/******************************************************************************/
/** 
 * @brief Get element stored at tree position pointed to by iterator
 * time complexity O(1).
 * @param _it : A tree iterator
 * @return the item the iterator points at or null if _it as at end
 */
void *BSTreeItrGet(BSTreeItr _it)
{
    Node *run = (Node *)_it;
    if(NULL == run)
    {
        return NULL;
    }
    return run->m_data;
}

/******************************************************************************/
/** 
 * @brief Get itertator to the next element from current iterator
 * complexity: O(?)
 *
 * @params _it : A tree iterator
 * @returns an iterator pointing at the next element after _it or end iterator.
 */
BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
    Node *run = (Node *)_it;
    if (NULL == _it)
    {
        return NULL;
    }


    if(run->m_right != NULL)
    {
        return FindMinElement((BSTreeItr)run->m_right);
    }

    if (run->m_right == NULL && (BSTreeItr)run == GetTheMostRightChild(_it))
    {
        return (BSTreeItr)run;
    }

    return FindYoungestFather(_it);
}

BSTreeItr BSTreeItrPrev(BSTreeItr _it)
{
    Node *run = (Node *)_it;
    if (NULL == _it)
    {
        return NULL;
    }
    /*check if _it is the most keft child*/
    if (GetTheMostLeftChild(_it) == _it)
    {
        return _it;
    }

    if(run->m_left == NULL)
    {
        return (BSTreeItr)run->m_father;
        /*root case - need improvement*/
    }

    /*get max in left sub tree*/
    /*run = FindMaxElement(_it);*/
    return FindMaxElement(_it);
}

static BSTreeItr FindMaxElement(BSTreeItr _it)
{
    Node* run = (Node*)_it;
    if(NULL == _it)
    {
        return NULL;
    }
    while(run->m_right != NULL)
    {
        run = run->m_right;
    }
    return (BSTreeItr)run;
}

static BSTreeItr GetTheMostLeftChild(BSTreeItr _it)
{
    Node *run = (Node *)_it;
    if (NULL == _it)
    {
        return NULL;
    }
    while (run->m_father != run->m_father->m_right)
    {
        run = run->m_father;
    }
    /*get the most left child*/
    while (run->m_left != NULL)
    {
        run = run->m_left;
    }

    return (BSTreeItr)run;
}

static BSTreeItr FindMinElement(BSTreeItr _it)
{
    Node *run = (Node *)_it;
    if (NULL == _it)
    {
        return NULL;
    }
    while (run->m_left != NULL)
    {
        run = run->m_left;
    }
    return (BSTreeItr)run;
}

static BSTreeItr GetTheMostRightChild(BSTreeItr _it)
{
    Node *run = (Node *)_it;
    if (NULL == _it)
    {
        return NULL;
    }
    while (run->m_father != run->m_father->m_right)
    {
        run = run->m_father;
    }
    /*get the most left child*/
    while (run->m_right != NULL)
    {
        run = run->m_right;
    }

    return (BSTreeItr)run;
}

static BSTreeItr FindYoungestFather(BSTreeItr _it)
{
    Node *run = (Node *)_it;
    if (NULL == _it)
    {
        return NULL;
    }
    while (run->m_father == run->m_father->m_right)
    {
        run = run->m_father;
    }
    return (BSTreeItr)run->m_father;
}
/*
static LessComparator GetIsLess(BSTreeItr _it)
{
    Node *run = (Node *)_it;
    while (run->m_father != run->m_father->m_right)
    {
        run = run->m_father;
    }
    return run->m_isLess;
}*/

/*typedef int (*ActionFunction)(void* _element, void* _context);*/


BSTreeItr BSTreeForEach(const BSTree* _tree, TreeTraversalMode _mode, ActionFunction _action, void* _context)
{
    Node* nodePtr = NULL;
    if(NULL == _tree || NULL == _tree->m_root.m_left || _tree->m_magic != TREE_VALID)
    {
        return NULL;
    }
    nodePtr = _tree->m_root.m_left;
    
    if(_mode == BSTREE_TRAVERSAL_PREORDER)
    {
        TreePrintPreOrder(nodePtr, _action, _context);
    }
    else if (_mode == BSTREE_TRAVERSAL_INORDER)
    {
        TreePrintInOrder(nodePtr, _action, _context);
    }
    else
    {
        TreePrintPostOrder(nodePtr, _action, _context);
    }
    return NULL;
}



/*****************************************************/

static void TreePrintInOrder(Node* nodePtr, ActionFunction _action, void* _context)
{
    if(nodePtr == NULL)
    {
        return;
    }
    TreePrintInOrder(nodePtr->m_left, _action, _context);
	_action(nodePtr->m_data, _context);
    TreePrintInOrder(nodePtr->m_right,_action ,_context);	
}

static void TreePrintPreOrder(Node* nodePtr, ActionFunction _action, void* _context)
{
    if(nodePtr == NULL)
    {
        return;
    }
	_action(nodePtr->m_data, _context);
    TreePrintPreOrder(nodePtr->m_left,_action ,_context);
    TreePrintPreOrder(nodePtr->m_right,_action ,_context);
    return;	
}

static void TreePrintPostOrder(Node* nodePtr, ActionFunction _action, void* _context)
{
    if(nodePtr == NULL)
    {
        return;
    }
    TreePrintPostOrder(nodePtr->m_left,_action ,_context);
    TreePrintPostOrder(nodePtr->m_right,_action ,_context);
	_action(nodePtr->m_data, _context);
    return;	
}


