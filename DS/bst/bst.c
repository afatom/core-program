#include "bst.h"
#include <stdio.h> 		/*printf*/
#include <stdlib.h>		/*malloc*/
#include "ADTDefs.h"

#define MAGIC 531773365

/******************************************************************************/
typedef struct Node {
	int 	m_data;
	struct 	Node* m_left;
	struct 	Node* m_right;
} Node;

struct Tree {
	Node*	m_root;
	size_t	m_magic;
};

/******************************************************************************/
Tree*	TreeCreate(void)
{
	Tree* treePtr = NULL;
	treePtr = (Tree*)malloc(sizeof(Tree));
	if(NULL == treePtr)
	{
		return NULL;
	}
	treePtr->m_magic = MAGIC;
	treePtr->m_root = NULL;
	return treePtr;
}

static void freeNodes(Node *nodePtr)
{
	if (nodePtr->m_left != NULL)
	{
		freeNodes(nodePtr->m_left);
	}
	if (nodePtr->m_right != NULL)
	{
		freeNodes(nodePtr->m_right);
	}
	free(nodePtr);
}
/******************************************************************************/
void	TreeDestroy(Tree* _tree)
{
	Node *nodePtr;
	if (NULL == _tree || NULL == _tree->m_root || _tree->m_magic == 0)
	{
		return;
	}
	nodePtr = _tree->m_root;
	freeNodes(nodePtr);
	_tree->m_magic = 0;
	free(_tree);

	/*
	if (NULL == _tree || NULL == _tree->m_root || _tree->m_magic == 0)
	{
		return;
	}

	if(_tree->m_root->m_left == NULL && _tree->m_root->m_right == NULL)
	{
		free(_tree->m_root);
		return;
	}
	_tree->m_root = _tree->m_root->m_left;
	free(_tree = _tree->m_root);
	_tree->m_root = _tree->m_root->m_right;
	free(_tree->m_root);
	//_tree = NULL;
	*/

}

/******************************************************************************/
static ADTErr CreateNode(Node** newNode, int data)
{
  *newNode = (Node*)malloc(sizeof(Node));
  if (NULL == *newNode)
  {
      return ERR_ALLOCATION_FAILED;
  }
  (*newNode)->m_data = data;
  return ERR_OK;
}
/******************************************************************************/
/*This function will link new nodes and sarc tree for aspecefic node*
*it will serve Insert and IsData found funcs as well
*in case we want to search tree we call this func with new node = NULL*/
static ADTErr SeekRightPlace(Tree* _tree, int data ,Node* newNode)
{
	Node* start = _tree->m_root;

	while (1)
	{
		if (start->m_data == data)
		{
			return ERR_NODE_OVERLAP; /*Collission*/
		}
		if(start->m_right != NULL && data > start->m_data)
		{
			/*move right*/
			start = start->m_right;
		}
		if(start->m_left != NULL && data < start->m_data)
		{
			/*move left*/
			start = start ->m_left;
		}
		if (start->m_right == NULL && data > start->m_data)
		{
			/*Connection point right*/
			start->m_right = newNode;
			return ERR_OK;
		}
		if (start->m_left == NULL && data < start->m_data)
		{
			/*Connection point left*/
			start->m_left = newNode;
			return ERR_OK;
		}
	}
}
/******************************************************************************/
ADTErr	TreeInsert(Tree* _tree, int _data)
{
	Node* newNode = NULL;
	ADTErr CreateResult;
	ADTErr insertRes;
	if (NULL == _tree)
	{
		return ERR_NOT_INITIALIZED;
	}
	if((CreateResult = CreateNode(&newNode, _data)) != ERR_OK)
	{
		return CreateResult;
	}
	/*first Node will be root Node*/
	if(_tree->m_root == NULL)
	{
		_tree->m_root = newNode;
		return ERR_OK;
	}

	if ((insertRes = SeekRightPlace(_tree, _data, newNode)) != ERR_OK)
	{
		free(newNode);
		return ERR_NODE_OVERLAP;
	}
	return ERR_OK;
}
/******************************************************************************/

int		TreeIsDataFound(Tree* _tree, int _data)
{
	ADTErr searchRes;
	if (NULL == _tree || NULL == _tree->m_root)
	{
		return 0;
	}
	if((searchRes = SeekRightPlace(_tree, _data, NULL)) == ERR_NODE_OVERLAP)
	{
		/*Exist*/
		return 1;
	}
	return 0;
}

static void TreePrintInOrder(Node* nodePtr)
{
	if (nodePtr->m_left != NULL)
	{
		TreePrintInOrder(nodePtr->m_left);
	}
	printf("[%d] ", nodePtr->m_data);
	if (nodePtr->m_right != NULL)
	{
		TreePrintInOrder(nodePtr->m_right);
	}
}

static void TreePrintPreOrder(Node* nodePtr)
{
	printf("[%d] ",nodePtr->m_data);
	if (nodePtr->m_left != NULL)
	{
		TreePrintPreOrder(nodePtr->m_left);
	}
	if(nodePtr->m_right != NULL)
	{
		TreePrintPreOrder(nodePtr->m_right);
	}
}

static void TreePrintPostOrder(Node* nodePtr)
{
	if (nodePtr->m_left != NULL)
	{
		TreePrintPostOrder(nodePtr->m_left);
	}
	if (nodePtr->m_right != NULL)
	{
		TreePrintPostOrder(nodePtr->m_right);
	}
	printf("[%d] ", nodePtr->m_data);
}
/******************************************************************************/
void	TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	Node* nptr = NULL;
	if (_tree == NULL)
	{
		puts("Empty Binary Search Tree");
		return;
	}
	nptr = _tree->m_root;
	if(NULL == nptr)
	{
		puts("Empty Tree");
	}
	switch(_traverseMode)
	{
		/*************************/
		case(PRE_ORDER):
			puts("PRE ORDER PRINT");
			TreePrintPreOrder(nptr);
			break;
		/*************************/
		case(IN_ORDER):
			puts("IN ORDER PRINT");
			TreePrintInOrder(nptr);
			break;
		/************************/
		case(POST_ORDER):
			puts("POST ORDER PRINT");
			TreePrintPostOrder(nptr);
			break;
		default: break;
	}
}
