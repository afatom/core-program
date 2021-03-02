#include "heap.h"
#include "vector.h"
#include <stdlib.h>     /*malloc*/
#include <stdio.h>
#include <assert.h>

#define HEAP_VALID 0xBEEFBEEF
#define HEAP_DESTROYED 0xDEADBEEF

#define TRUE 1
#define FALSE 0

typedef struct HeapItem{
	size_t m_itemIndex;
	void* m_itemValue;
}HeapItem;


struct Heap
{
    /*size_t  m_magic;*/ /*No Need for heap magic. we will exploit vector magic*/
    Vector* m_vec;
    size_t  m_heapSize;
    LessThanComparator m_pfLess;
};

/******************************************************************************************/
static void VectorTurnToHeap(Heap *heap);
static void Swap(Heap *heap, size_t _firstIndex, size_t _secIndex);
static void ReheapifyDownward(Heap *_heap);
static void VectorTurnToHeap(Heap *heap);
static void BubbleUp(Heap *_heap);
static void BubbleUp(Heap *_heap);
static void MaxHeapifyTree(Heap* _heap, size_t _parent);
static size_t FindMaxNodeIndex(Heap *_heap, size_t _parent);
/******************************************************************************************/

Heap *HeapBuild(Vector *_vector, LessThanComparator _pfLess)
{
    Heap *heap = NULL;
    void* item = NULL;
    VectorResult status;
    /*for test issues only - check vector validity*/
    status = VectorGet(_vector, 1, &item);
    if(status == VECTOR_UNITIALIZED_ERROR || NULL == _pfLess)
    {
    	return NULL;
    }
    
    /*alocating heap*/
    heap = (Heap*)malloc(sizeof(Heap));
    if (NULL == heap)
    {
        return NULL;
    }
    heap->m_vec = _vector;                            /*linking to main vector*/
    heap->m_heapSize = VectorSize(_vector);          /*initial size is num of vector items*/

    heap->m_pfLess = _pfLess;
  

    VectorTurnToHeap(heap);

    return heap;
}
/******************************************************************************/

Vector *HeapDestroy(Heap **_heap)
{
    Vector *vecPtr = NULL;
    if (NULL==_heap || NULL == *_heap )
    {
        return NULL;
    }
    /*destroy point*/
  
    vecPtr = (*_heap)->m_vec; /*save link to vector befor destroying heap*/
    free(*_heap);
    *_heap=NULL;
    return vecPtr; /*return Vector to main*/

}
/******************************************************************************/

HeapResult HeapInsert(Heap *_heap, void *_element)
{
	void* item = NULL;
    VectorResult status;
    /*for test issues only - check vector validity*/
    status = VectorGet(_heap->m_vec, 1, &item);
    if(status == VECTOR_UNITIALIZED_ERROR || NULL == _heap)
    {
    	return HEAP_NOT_INITIALIZED;
    }
    
    if(NULL == _element)
    {
        return HEAP_IVALID_DATA_IN;
    }

    if ((status = VectorAppend(_heap->m_vec, _element)) != VECTOR_SUCCESS)
    {
        return status;
    }
    ++_heap->m_heapSize;
    BubbleUp(_heap);
    return HEAP_SUCCESS;
    
}
/******************************************************************************/

const void *HeapPeek(const Heap *_heap)
{
    void* maxElement = NULL;
    VectorResult status;
    void* item = NULL;
    /*for test issues only - check vector validity*/
    status = VectorGet(_heap->m_vec, 1, &item);
    if(status == VECTOR_UNITIALIZED_ERROR || NULL == _heap)
    {
    	return NULL;
    }

    VectorGet(_heap->m_vec, 1, &maxElement);
    return maxElement;
}
/******************************************************************************/
size_t HeapSize(const Heap *_heap)
{
    VectorResult status;
    void* item = NULL;
    /*for test issues only - check vector validity*/
    status = VectorGet(_heap->m_vec, 1, &item);
    if(status == VECTOR_UNITIALIZED_ERROR || NULL == _heap)
    {
    	return 0;
    }

    return _heap->m_heapSize;

}
/******************************************************************************/
void *HeapExtract(Heap *_heap)
{
    void* maximum = NULL;   
    VectorResult status;
    void* item = NULL;
    /*for test issues only - check vector validity*/
    status = VectorGet(_heap->m_vec, 1, &item);
    if(status == VECTOR_UNITIALIZED_ERROR || NULL == _heap || _heap->m_heapSize <1)
    {
    	return NULL;
    }
    /*get maximum elem*/
    Swap(_heap, 1, _heap->m_heapSize);
    VectorRemove(_heap->m_vec, &maximum);
    _heap->m_heapSize -=1;
    ReheapifyDownward(_heap);
    return maximum;
}
/*****************************************************************************/

void HeapSort(Vector *_vec, LessThanComparator _pfLess)
{
    Heap* heap = NULL;
    VectorResult status;
    void* item = NULL;
    /*for test issues only - check vector validity*/
    status = VectorGet(_vec, 1, &item);
    if(status == VECTOR_UNITIALIZED_ERROR || NULL == _pfLess || VectorSize(_vec)==0)
    {
    	return;
    }
    
    heap = HeapBuild(_vec, _pfLess);
    while(heap->m_heapSize > 1)
    {
        Swap(heap, 1, heap->m_heapSize);
        --heap->m_heapSize;
        ReheapifyDownward(heap);
    }
    HeapDestroy(&heap);
    heap=NULL;
    return;
}


/******************************************************************************/
size_t HeapForEach(const Heap *_heap, ActionFunction _action, void *_context)
{
    void *elem;
    size_t i;
    
    VectorResult status;
    void* item = NULL;
   if(NULL == _action || NULL == _heap)
    {
    	return 0;
    }
 
    /*for test issues only - check vector validity*/
    status = VectorGet(_heap->m_vec, 1, &item);
    if(status == VECTOR_UNITIALIZED_ERROR)
    {
    	return 0;
    } 
    
    
    for (i = 1; i < VectorSize(_heap->m_vec); ++i)
    {
        VectorGet(_heap->m_vec, i, &elem);
        _action(elem, _context);
    }
    return i;
}

/*****************************************************************************/
/********************* Static Functions Segment ******************************/
/*****************************************************************************/


static void ReheapifyDownward(Heap *_heap)
{
    size_t parent = 1, newParent=0;

    while(parent <= _heap->m_heapSize/2)
    {
        newParent =  FindMaxNodeIndex(_heap, parent);
        if(newParent == parent)
        {
            return;
        }
        Swap(_heap, parent, newParent);
        parent = newParent;
    }
    return;
}


/*****************************************************************************/
/*****************************************************************************/

static size_t FindMaxNodeIndex(Heap *_heap, size_t _parent)
{
	HeapItem LeftChild, RightChild, Largest;
	/*parent*/
	Largest.m_itemIndex = _parent;
	VectorGet(_heap->m_vec, Largest.m_itemIndex, &Largest.m_itemValue);
	/*left child*/
	LeftChild.m_itemIndex = 2*_parent;
	VectorGet(_heap->m_vec, LeftChild.m_itemIndex, &LeftChild.m_itemValue);
	/*right child*/
	RightChild.m_itemIndex = 2*_parent + 1;
	VectorGet(_heap->m_vec, RightChild.m_itemIndex, &RightChild.m_itemValue);
	

    if (LeftChild.m_itemIndex <= _heap->m_heapSize && _heap->m_pfLess(Largest.m_itemValue, LeftChild.m_itemValue) == TRUE)
    {
        Largest = LeftChild;
    }

    if (RightChild.m_itemIndex <= _heap->m_heapSize && _heap->m_pfLess(Largest.m_itemValue, RightChild.m_itemValue) == TRUE)
    {
        Largest = RightChild;
    }

    return Largest.m_itemIndex;
}

/*****************************************************************************/
/*****************************************************************************/
static void MaxHeapifyTree(Heap* _heap, size_t _parent)
{
    size_t largest = 0;
    largest = FindMaxNodeIndex(_heap, _parent);
    if(largest == _parent)
    {
        return;
    }

    Swap(_heap, _parent, largest);
    MaxHeapifyTree(_heap, largest);
}

/*****************************************************************************/
/*****************************************************************************/

static void Swap(Heap *heap, size_t _firstIndex, size_t _secIndex)
{

    void* temp1 = NULL;
    void* temp2 = NULL;
    VectorGet(heap->m_vec, _firstIndex, &temp1);
    VectorGet(heap->m_vec, _secIndex, &temp2);
    VectorSet(heap->m_vec, _firstIndex, temp2);
    VectorSet(heap->m_vec, _secIndex, temp1);
}
/******************************************************************************/
/******************************************************************************/
static void VectorTurnToHeap(Heap *heap)
{
    
    
    size_t i;
    /*assert(VectorSize(heap->m_vec) == 15);
    assert(heap->m_heapSize == 15);
*/
    for (i = heap->m_heapSize / 2;  i > 0 ; --i)
    {
        /*shiftup(heap,i);*/
        MaxHeapifyTree(heap, i);
    }
    return;
}
/*****************************************************************************/
/*****************************************************************************/

static void BubbleUp(Heap *_heap)
{
    size_t sonIndex = _heap->m_heapSize;
    size_t fatherIndex = (sonIndex) / 2;
    void* sonValue = NULL; 
    void* fatherValue = NULL;
    VectorGet(_heap->m_vec, fatherIndex, &fatherValue);
    VectorGet(_heap->m_vec, sonIndex, &sonValue);

    while (sonIndex > 1 &&   (_heap->m_pfLess(fatherValue, sonValue) == TRUE))
    {
        Swap(_heap, fatherIndex, sonIndex);
        sonIndex = fatherIndex;
        fatherIndex = (sonIndex ) / 2;
        VectorGet(_heap->m_vec, fatherIndex, &fatherValue);
        VectorGet(_heap->m_vec, sonIndex, &sonValue);
    }
}
/******************************************************************************/
