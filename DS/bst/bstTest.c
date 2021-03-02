#include "bst.h"
#include "mu_test.h"
#include "ADTDefs.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h> 

UNIT(create_destroy_tree)
	Tree* tree;
	tree = TreeCreate();
	ASSERT_THAT(tree != NULL);
	TreeDestroy(tree);
END_UNIT

UNIT(insert_once)
	Tree* tree;
	tree = TreeCreate();
	ASSERT_THAT(tree != NULL);
	ASSERT_THAT(TreeInsert(tree, 5) == ERR_OK);
	TreeDestroy(tree);
END_UNIT

UNIT(insert_multiple_ascending)
	Tree* tree;
	int i;
	tree = TreeCreate();
	ASSERT_THAT(tree != NULL);
	for (i = 0; i < 100; ++i)
	{
		ASSERT_THAT(TreeInsert(tree, i) == ERR_OK);
	}
	TreeDestroy(tree);
END_UNIT

UNIT(insert_multiple_descending)
	Tree* tree;
	int i;
	tree = TreeCreate();
	ASSERT_THAT(tree != NULL);
	for (i = 100; i > 0; --i)
	{
		ASSERT_THAT(TreeInsert(tree, i) == ERR_OK);
	}
	TreeDestroy(tree);
END_UNIT
/*

UNIT(insert_existing)
	Tree* tree;
	int i;
	tree = TreeCreate();
	ASSERT_THAT(tree != NULL);
	for (i = 100; i > 0; --i)
	{
		ASSERT_THAT(TreeInsert(tree, i) == ERR_OK);
	}
	ASSERT_THAT(TreeInsert(tree, 55) == ERR_NODE_OVERLAP);
	TreeDestroy(tree);
END_UNIT

UNIT(insert_random)
	Tree* tree;
	ADTErr err;
	int i;
	tree = TreeCreate();
	ASSERT_THAT(tree != NULL);
	srand((unsigned int)time(NULL));
	for (i = 100; i > 0; --i)
	{
		err = TreeInsert(tree, rand() % 1000);
		ASSERT_THAT(err == ERR_OK || err == ERR_NODE_OVERLAP);
	}
	TreeDestroy(tree);
END_UNIT

UNIT(is_found_true)
	Tree* tree;
	int i;
	tree = TreeCreate();
	ASSERT_THAT(tree != NULL);
	for (i = 100; i > 0; --i)
	{
		ASSERT_THAT(TreeInsert(tree, i) == ERR_OK);
	}
	ASSERT_THAT(TreeIsDataFound(tree, 55));
	TreeDestroy(tree);
END_UNIT

UNIT(is_found_false)
	Tree* tree;
	int i;
	tree = TreeCreate();
	ASSERT_THAT(tree != NULL);
	for (i = 100; i > 0; --i)
	{
		ASSERT_THAT(TreeInsert(tree, i) == ERR_OK);
	}
	ASSERT_THAT(!TreeIsDataFound(tree, 500));
	TreeDestroy(tree);
END_UNIT

UNIT(insert_null)
	ASSERT_THAT(TreeInsert(NULL, 55) == ERR_NOT_INITIALIZED);
END_UNIT

UNIT(is_found_null)
	ASSERT_THAT(!TreeIsDataFound(NULL, 55));
END_UNIT
*/
TEST_SUITE(BST_Test)
	TEST(create_destroy_tree)
	TEST(insert_once)
	TEST(insert_multiple_ascending)
	TEST(insert_multiple_descending)
	/*
	TEST(insert_existing)
	TEST(insert_random)
	TEST(is_found_true)
	TEST(is_found_false)
	TEST(insert_null)
	TEST(is_found_null)*/
END_SUITE

