#include "bin_tree.h"
#include <stdlib.h>
#include "mu_test.h"
#include <stdio.h>
#include <time.h>
#include <stdio.h>




#define TRUE  1
#define FALSE 0
#define SIZE 10
#define NUM 1000

typedef struct Person {
    int m_age;
    char m_name[16];
    int m_edu;
}Person;

/***********************************/
/* bold - not bold */
#define BOLD_ON         "\x1b[1m"
#define BOLD_OFF        "\x1b[21m"
/***********************************/
/* colors */
#define NORMAL          "\x1B[0m"
#define BLACK           "\x1b[30m"
#define RED             "\x1B[31m"
#define GREEN           "\x1B[32m"
#define YELLOW          "\x1B[33m"
#define BLUE            "\x1B[34m"
#define MAGENTA         "\x1B[35m"
#define CYAN            "\x1B[36m"
#define WHITE           "\x1B[37m"
#define GRAY            "\x1b[90m"
/***********************************/
/* cards suites symbols */
#define _HEART_           "\xE2\x99\xA5"
#define _SPADE_           "\xE2\x99\xA0"
#define _DIAMOND_         "\xE2\x99\xA6"
#define _CLUB_            "\xE2\x99\xA3"

/***********************************/




typedef enum {
    NORMALL=1,
    REDD,
    BLUEE,
    GREENN
}COLOR;

/*
static int	TreePrint(void* _element, void* _context)
{
    Person* per = (Person*)_element;

    if(_context == NULL)
    {
        printf("Person Age is: %d\n", per->m_age);
    }

    else if( *(COLOR*)_context == NORMALL)
    {
        printf("Person Age is: %d\n", per->m_age);
    }
    
    else if (*(COLOR*)_context == REDD)
    {
        puts("*");
        printf(RED"Person Age is: %d\n"NORMAL, per->m_age );
    }
    else if (*(COLOR*)_context == GREENN)
    {
        printf(GREEN"Person Age is: %d\n"NORMAL, per->m_age );
    }
    else 
    {
        printf(BLUE"Person Age is: %d\n"NORMAL, per->m_age );
    }
    return 1;

}
*/




int LessCompare(void* _left, void* _right)
{
    return ((Person*)_left < (Person*)_right) ? (TRUE) : (FALSE);
}

/*
static void swap(int* arr, int firstindex, int secindex)
{
    int firstval, secval;
    firstval =  arr[firstindex];
    secval =  arr[secindex];
    arr[secindex] = firstval;
    arr[firstindex]= secval;
    return;
}

*/
/*
static void ShuffleArray(int* _arr, int _size)
{
    int i, newIndex;
    for (i = _size -1; i >= 0; --i)
    {
        newIndex = rand() % (i+1);
        swap(_arr, i, newIndex);
    }
}
*/

UNIT(ssssrand)
srand((unsigned int)time(NULL));
END_UNIT

/*****************************************/
UNIT(Create_NULL_Function_Pointer_Test)
    BSTree* tree = NULL; 
    tree = BSTreeCreate(NULL);
    ASSERT_THAT (NULL == tree);
    tree = BSTreeCreate(NULL);
    ASSERT_THAT (NULL == tree);
    BSTreeDestroy(&tree, NULL);
    BSTreeDestroy(&tree, NULL);
    ASSERT_THAT(NULL == tree);
END_UNIT
/*****************************************/
UNIT(Create_And_Destroy_Normal_Inputs_Test)
    BSTree *tree = NULL;
    tree = BSTreeCreate(NULL);
    ASSERT_THAT(NULL == tree);
    tree = BSTreeCreate(LessCompare);
    ASSERT_THAT(NULL != tree);
    BSTreeDestroy(&tree, NULL);
    BSTreeDestroy(&tree, NULL);
    ASSERT_THAT(NULL == tree);
END_UNIT
/*****************************************/

UNIT(Insert_Few_Elements_Test)
    BSTree* tree = NULL; 
    BSTreeItr it = NULL;
    Person** arr = NULL;
    int i;

    arr = malloc(SIZE * sizeof(*arr));
    for(i = 0; i < SIZE; ++i)
    {
        arr[i]=malloc(sizeof(Person));
    }

    for(i = 0; i < SIZE; ++i)
    {
        arr[i]->m_age = 30*i;
        arr[i]->m_edu = 10*i;
    }

    tree = BSTreeCreate(NULL);
    ASSERT_THAT (NULL == tree);
    tree = BSTreeCreate(LessCompare);
    ASSERT_THAT (NULL != tree);

    for(i = 0; i<SIZE ; ++i)
    {
        ASSERT_THAT( (it = BSTreeInsert(tree, (void*)arr[i])) != NULL);
    }

    BSTreeDestroy(&tree, NULL);
    BSTreeDestroy(&tree, NULL);
    ASSERT_THAT(NULL == tree);
END_UNIT
/*****************************************

UNIT(Insert__Random__Test)
    
    TreeTraversalMode  order = BSTREE_TRAVERSAL_INORDER;
    BSTree* tree = NULL; 
    BSTreeItr it = NULL;
    int arr[NUM], i;
    Person* prr[NUM];
    for(i = 0; i < NUM; ++i)
    {
        arr[i] = i;
    }
    ShuffleArray(arr, NUM);
    for(i = 0; i< NUM; ++i)
    {
       
        prr[i] = malloc(sizeof(*prr[i]));
        prr[i]->m_age = i;
    }

    tree = BSTreeCreate(LessCompare);
    ASSERT_THAT (NULL != tree);
    tree = BSTreeCreate(LessCompare);
    ASSERT_THAT (NULL != tree);

    for(i=0;i<NUM;++i)
    {
        ASSERT_THAT( (it = BSTreeInsert(tree, (void*)prr[arr[i]])) != NULL);
    }

    for(i = 0; i< NUM; ++i)
    {
        free(prr[i]);
    }
    
    
    BSTreeForEach(tree, order, TreePrint, NULL);
    BSTreeDestroy(&tree, NULL);
    BSTreeDestroy(&tree, NULL);
    ASSERT_THAT(NULL == tree);

END_UNIT

*/




/*****************************************/

TEST_SUITE(Generic_BST_Test)
TEST(ssssrand)
TEST(Create_NULL_Function_Pointer_Test)
TEST(Create_And_Destroy_Normal_Inputs_Test)
/*
    TEST(Insert__Basic__Test)
    TEST(Insert__Random__Test)
    */
END_SUITE




