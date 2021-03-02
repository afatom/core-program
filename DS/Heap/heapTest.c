#include "vector.h"
#include "heap.h"
#include "ADTDefs.h"
#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"

/**************************************************/ /*TEST 1*/ /*Create Test*/
UNIT(Heap_Create_And_Destroy_Test)
    size_t _initialSize = 20, _extensionBblockSize = 20;
    size_t _numOfItems;
    Heap* heap = NULL;
    Vector *vec = NULL;
    vec = VectorCreate(_initialSize, _extensionBblockSize);
    VectorAdd(vec, 1);
    VectorAdd(vec, 1);
    VectorAdd(vec, 1);
    VectorAdd(vec, 1);
    heap = HeapBuild(vec);
    ASSERT_THAT(NULL != heap);
    vec = HeapDestroy(heap);
    ASSERT_THAT(NULL != vec);
    VectorItemsNum(vec, &_numOfItems);
    ASSERT_THAT(_numOfItems == 4);
    VectorDestroy(vec);
END_UNIT

UNIT(Heap_Create_Null_Test)
Vector *vec = NULL;
Heap *heap = NULL;
heap = HeapBuild(vec);
ASSERT_THAT(NULL == heap);
END_UNIT

UNIT(Heap_Destroy_Null_Test)
    Vector *vec = NULL;
    Heap *heap = NULL;
    heap = HeapBuild(vec);
    ASSERT_THAT(NULL == heap);
    ASSERT_THAT(NULL == HeapDestroy(heap));
END_UNIT
/**************************************************/ /*TEST 2*/ /*Double Destroy Test*/
UNIT(Heap_Double_Destroy_Test)
    size_t _initialSize = 20, _extensionBblockSize = 20;
    size_t _numOfItems;
    Heap *heap = NULL;
    Vector *vec = VectorCreate(_initialSize, _extensionBblockSize);
    VectorAdd(vec, 1);
    VectorAdd(vec, 1);
    VectorAdd(vec, 1);
    VectorAdd(vec, 1);
    heap = HeapBuild(vec);
    ASSERT_THAT(NULL != heap);
    vec = HeapDestroy(heap);
    HeapDestroy(heap);
    ASSERT_THAT(NULL != vec);
    VectorItemsNum(vec, &_numOfItems);
    ASSERT_THAT(_numOfItems == 4);
    VectorDestroy(vec);
END_UNIT



UNIT(Heap_Max_Test)
    size_t _initialSize = 20, _extensionBblockSize = 20;
    size_t _numOfItems;
    int _data;
    ADTErr status;
    Vector *vec = VectorCreate(_initialSize, _extensionBblockSize);
    Heap *heap = NULL;
    VectorAdd(vec, 1);
    VectorAdd(vec, 2);
    VectorAdd(vec, 3);
    VectorAdd(vec, 4);
    heap = HeapBuild(vec);
    ASSERT_THAT(NULL != heap);
    ASSERT_THAT((status = HeapMax(heap, &_data)) == ERR_OK);
    ASSERT_THAT(_data == 4);
    vec = HeapDestroy(heap);
    ASSERT_THAT(NULL != vec);
    VectorItemsNum(vec, &_numOfItems);
    ASSERT_THAT(_numOfItems == 4);
    VectorDestroy(vec);
END_UNIT

UNIT(Heap_Insert_To_Empty_Vector_Test)
    size_t _initialSize = 20, _extensionBblockSize = 20;
    size_t _numOfItems;
    int _data;
    Heap *heap = NULL;
    ADTErr status;
    Vector *vec = VectorCreate(_initialSize, _extensionBblockSize);
    heap = HeapBuild(vec);
    ASSERT_THAT(NULL != heap);
    ASSERT_THAT((status = HeapInsert(heap, 1)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 88)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 7)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 15)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 13)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 20)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 90)) == ERR_OK);
    ASSERT_THAT((status = HeapMax(heap, &_data)) == ERR_OK);
    ASSERT_THAT(_data == 90);

    VectorItemsNum(vec, &_numOfItems);
    ASSERT_THAT(_numOfItems == 7);
    ASSERT_THAT(7 == HeapItemsNum(heap));

    vec = HeapDestroy(heap);
    ASSERT_THAT(NULL != vec);
    VectorDestroy(vec);
END_UNIT


UNIT(Heap_Extract_Max__Normal_Test)
    size_t _initialSize = 20, _extensionBblockSize = 20;
    int _data1 = 0, _data2 = 0;
    ADTErr status;
    Vector *vec = VectorCreate(_initialSize, _extensionBblockSize);
    Heap *heap = HeapBuild(vec);
    ASSERT_THAT(NULL != heap);
    ASSERT_THAT((status = HeapInsert(heap, 1)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 88)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 7)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 15)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 13)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 20)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 90)) == ERR_OK);
    ASSERT_THAT((status = HeapMax(heap, &_data1)) == ERR_OK);
    ASSERT_THAT(_data1 == 90);
    ASSERT_THAT(7 == HeapItemsNum(heap));
    ASSERT_THAT(HeapExtractMax(heap, &_data2) == ERR_OK);
    ASSERT_THAT(_data2 == 90);
    vec = HeapDestroy(heap);
    ASSERT_THAT(NULL != vec);
    VectorDestroy(vec);
END_UNIT

UNIT(Heap_Extract_Max_Empty_Vector_Test)
    size_t _initialSize = 20, _extensionBblockSize = 20;
    int _data = 0;
    ADTErr status;
    Vector *vec = VectorCreate(_initialSize, _extensionBblockSize);
    Heap *heap = HeapBuild(vec);
    ASSERT_THAT(NULL != heap);
    ASSERT_THAT((status = HeapMax(heap, &_data)) == ERR_WRONG_INDEX);
    ASSERT_THAT(_data == 0);
    ASSERT_THAT(0 == HeapItemsNum(heap));
    ASSERT_THAT(HeapExtractMax(heap, &_data) == ERR_UNDERFLOW);
    vec = HeapDestroy(heap);
    ASSERT_THAT(NULL != vec);
    VectorDestroy(vec);
END_UNIT

UNIT(Heap_Extract_Max_Max_Rson_Test)
    size_t _initialSize = 20, _extensionBblockSize = 20;
    int _data1 = 0, _data2 = 0;
    ADTErr status;
    Vector *vec = VectorCreate(_initialSize, _extensionBblockSize);
    Heap *heap = HeapBuild(vec);
    ASSERT_THAT(NULL != heap);
    ASSERT_THAT((status = HeapInsert(heap, 5)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 7)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 20)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 1)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 9)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 30)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 40)) == ERR_OK);
    ASSERT_THAT((status = HeapMax(heap, &_data1)) == ERR_OK);
    ASSERT_THAT(_data1 == 40);
    ASSERT_THAT(7 == HeapItemsNum(heap));
    ASSERT_THAT(HeapExtractMax(heap, &_data2) == ERR_OK);
    ASSERT_THAT(_data2 == 40);
    vec = HeapDestroy(heap);
    ASSERT_THAT(NULL != vec);
    VectorDestroy(vec);
END_UNIT

UNIT(Heap_Extract_Max_Max_Lson_Test)
    size_t _initialSize = 20, _extensionBblockSize = 20;
    int _data1 = 0, _data2 = 0;
    ADTErr status;
    Vector *vec = VectorCreate(_initialSize, _extensionBblockSize);
    Heap *heap = HeapBuild(vec);
    ASSERT_THAT(NULL != heap);
    ASSERT_THAT((status = HeapInsert(heap, 5)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 7)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 20)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 1)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 9)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 45)) == ERR_OK);
    ASSERT_THAT((status = HeapInsert(heap, 30)) == ERR_OK);
    ASSERT_THAT((status = HeapMax(heap, &_data1)) == ERR_OK);
    ASSERT_THAT(_data1 == 45);
    ASSERT_THAT(7 == HeapItemsNum(heap));
    ASSERT_THAT(HeapExtractMax(heap, &_data2) == ERR_OK);
    ASSERT_THAT(_data2 == 45);
    vec = HeapDestroy(heap);
    ASSERT_THAT(NULL != vec);
    VectorDestroy(vec);
END_UNIT

UNIT(Heap_Conv_Test)
size_t _initialSize = 20, _extensionBblockSize = 20;
Heap *heap = NULL;
Vector *vec = VectorCreate(_initialSize, _extensionBblockSize);
VectorAdd(vec, 0);
VectorAdd(vec, 7);
VectorAdd(vec, 2);
VectorAdd(vec, 8);
VectorAdd(vec, 10);
VectorAdd(vec, 1);
VectorAdd(vec, 9);

heap = HeapBuild(vec);
/*HeapPrint(heap);*/
vec = HeapDestroy(heap);
ASSERT_THAT(NULL != vec);
VectorDestroy(vec);
END_UNIT

/******************************************************/
/*Main function Macro*/
TEST_SUITE(Heap Test)
    TEST(Heap_Create_And_Destroy_Test)
    TEST(Heap_Double_Destroy_Test)
    TEST(Heap_Max_Test)
    TEST(Heap_Create_Null_Test)
    TEST(Heap_Destroy_Null_Test)
    TEST(Heap_Insert_To_Empty_Vector_Test)
    TEST(Heap_Extract_Max_Empty_Vector_Test)
    TEST(Heap_Extract_Max__Normal_Test)
    TEST(Heap_Extract_Max_Max_Rson_Test)
    TEST(Heap_Extract_Max_Max_Lson_Test)
    TEST(Heap_Conv_Test)
END_SUITE
