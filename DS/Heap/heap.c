#include "vector.h"
#include "heap.h"
#include "ADTDefs.h"
#include <stddef.h>    /*size_t*/
#include <stdio.h>

#define MAGIC 531773389
/******************************************************************************/
struct Heap {
  size_t    m_magic;
  size_t    m_heapSize;
  Vector*   m_vec;
};
/*******************************************************************************/
static void Swap(Heap *heap, size_t first, size_t sec);
static void shiftup(Heap *_heap, size_t index);
static void VectorTurnToHeap(Heap *heap);
static ADTErr SwapFirstWithLast(Vector *_vec);
static void BubbleUp(Heap *_heap);
static void Heapify(Heap *_heap);

/******************************************************************************/
Heap *HeapBuild(Vector *_vec)
{
  Heap* heap = NULL;
  if (NULL == _vec) /*main send us null vector*/
  {
    return NULL;
  }
  /*alocating heap*/
  heap = (Heap*)malloc(sizeof(Heap));
  if (NULL == heap)
  {
    return NULL;
  }
  heap->m_vec = _vec; /*linking to main vector*/
  VectorItemsNum(heap->m_vec, &(heap->m_heapSize)); /*initial size is num of vector items*/
  VectorTurnToHeap(heap);
  heap->m_magic = MAGIC;

  return heap;
}
/******************************************************************************/
Vector* HeapDestroy(Heap* _heap)
{
  Vector* vecPtr = NULL;
  if (NULL == _heap || _heap->m_magic == 0)
  {
    return NULL;
  }
  /*destroy point*/
  vecPtr = _heap->m_vec; /*save link to vector befor destroying heap*/
  _heap->m_magic = 0;
  free(_heap);
  return vecPtr; /*return Vector to main*/
}
/******************************************************************************/
void HeapPrint(const Heap *_heap)
{
  if (NULL == _heap)
  {
    puts("Empty Heap!");
    return;
  }
  VectorPrint(_heap->m_vec);
}
/******************************************************************************/
ADTErr HeapMax(const Heap *_heap, int *_data)
{

  if(NULL == _heap || NULL == _heap->m_vec)
  {
    return ERR_NOT_INITIALIZED;
  }
  if (NULL == _data)
  {
    return ERR_GENERAL;
  }
  /*maybe if items num = zero we return err*/
  return VectorGet(_heap->m_vec, 0, _data);
}
/******************************************************************************/
ADTErr HeapExtractMax(Heap *_heap, int *_data)
{
  ADTErr swapStatus;
  if (NULL == _heap || NULL == _heap->m_vec)
  {
    return ERR_NOT_INITIALIZED;
  }
  if (NULL == _data)
  {
    return ERR_GENERAL;
  }
  /*vectordelete o index call swapfirstwithlast*/
  /*heapify again*/
  if ((swapStatus = SwapFirstWithLast(_heap->m_vec)) != ERR_OK)
  {
    return swapStatus;
  }
  if (VectorDelete(_heap->m_vec, _data) != ERR_OK)
  {
    return VectorDelete(_heap->m_vec, _data);
  }
  --_heap->m_heapSize;
  Heapify(_heap);
  return ERR_OK;
}
/******************************************************************************/
size_t HeapItemsNum(const Heap *_heap)
{
  size_t _numOfItems;
  if (NULL == _heap || NULL == _heap->m_vec)
  {
    return ERR_NOT_INITIALIZED;
  }
  VectorItemsNum(_heap->m_vec, &_numOfItems);
  return _numOfItems;
}
/******************************************************************************/
ADTErr HeapInsert(Heap *_heap, int _data)
{
  ADTErr status;
  if (NULL == _heap || NULL == _heap->m_vec)
  {
    return ERR_NOT_INITIALIZED;
  }

  if((status = VectorAdd(_heap->m_vec, _data))!=ERR_OK)
  {
    return status;
  }
  ++_heap->m_heapSize;
  BubbleUp(_heap);
  return ERR_OK;
}
/*****************************************************************************/
/********************* Static Functions Segment ******************************/
/*****************************************************************************/

static void Swap(Heap *heap, size_t first, size_t sec)
{

  int firstVal, secVal;
  VectorGet(heap->m_vec, first, &firstVal);
  VectorGet(heap->m_vec, sec, &secVal);
  VectorSet(heap->m_vec, first, secVal);
  VectorSet(heap->m_vec, sec, firstVal);
}
/******************************************************************************/
static void shiftup(Heap *_heap, size_t index)
{
  size_t fatherIndex, lSon, rSon;
  int lSonValue, rSonValue, fatherValue;
  fatherIndex = index;
  lSon = fatherIndex * 2 + 1;
  rSon = fatherIndex * 2 + 2;
  VectorGet(_heap->m_vec, fatherIndex, &fatherValue);
  if (rSon <= _heap->m_heapSize - 1) /*2 sons*/
  {

    VectorGet(_heap->m_vec, lSon, &lSonValue);
    VectorGet(_heap->m_vec, rSon, &rSonValue);
    if (fatherValue > lSonValue && fatherValue > rSonValue) /*correct heap*/
    {
      return;
    }
    if (fatherValue < lSonValue && lSonValue > rSonValue) /*swap with the left son*/
    {
      Swap(_heap, fatherIndex, lSon);
      /*printf(" swap %d %d\n", fatherValue, lSonValue);*/
      shiftup(_heap, lSon);
    }
    else /*swap with the right son*/
    {
      Swap(_heap, fatherIndex, rSon);
      /*printf(" swap %d %d\n", fatherValue, rSonValue);*/
      shiftup(_heap, rSon);
    }
  }
  else if (lSon <= _heap->m_heapSize - 1) /*have 1 son*/
  {
    VectorGet(_heap->m_vec, lSon, &lSonValue);
    if (fatherValue > lSonValue) /*correct heap*/
    {
      return;
    }
    if (fatherValue < lSonValue) /*swap with the left son*/
    {
      Swap(_heap, fatherIndex, lSon);
      /*printf(" swap %d %d\n", fatherValue, lSonValue);*/
      shiftup(_heap, lSon);
    }
  }
  else /*0 sons , I reach a leafe stop the function*/
  {
    return;
  }
}
/******************************************************************************/
static void VectorTurnToHeap(Heap *heap)
{
  int i;
  for (i = (heap->m_heapSize - 1) / 2; i >= 0; --i)
  {
    shiftup(heap, i);
  }
}
/******************************************************************************/
static ADTErr SwapFirstWithLast(Vector *_vec)
{
  ADTErr status;
  size_t numOfItems;
  int lastElement;
  int firstElement;
  /*get last item*/
  if ((status = VectorItemsNum(_vec, &numOfItems)) != ERR_OK)
  {
    return status;
  }
  VectorGet(_vec, 0, &firstElement);
  VectorGet(_vec, numOfItems - 1, &lastElement);
  VectorSet(_vec, 0, lastElement);
  VectorSet(_vec, numOfItems - 1, firstElement);
  return ERR_OK;
}
/******************************************************************************/
static void Heapify(Heap *_heap)
{
  size_t fatherIndex = 0;
  size_t lSon;
  size_t rSon;
  int lSonValue, rSonValue, fatherValue;

  while (fatherIndex < _heap->m_heapSize)
  {
    lSon = fatherIndex * 2 + 1;
    rSon = fatherIndex * 2 + 2;
    VectorGet(_heap->m_vec, fatherIndex, &fatherValue);

    if (rSon <= _heap->m_heapSize - 1) /*2 sons*/
    {
      VectorGet(_heap->m_vec, lSon, &lSonValue);
      VectorGet(_heap->m_vec, rSon, &rSonValue);
      if (fatherValue > lSonValue && fatherValue > rSonValue) /*correct heap*/
      {
        return;
      }
      if (fatherValue < lSonValue && lSonValue > rSonValue) /*swap with the left son*/
      {
        Swap(_heap, fatherIndex, lSon);
        fatherIndex = lSon;
      }
      else /*swap with the right son*/
      {
        Swap(_heap, fatherIndex, rSon);
        fatherIndex = rSon;
      }
    }
    else if (lSon <= _heap->m_heapSize - 1) /*have 1 son*/
    {
      VectorGet(_heap->m_vec, lSon, &lSonValue);
      if (fatherValue > lSonValue) /*correct heap*/
      {
        return;
      }
      if (fatherValue < lSonValue) /*swap with the left son*/
      {
        Swap(_heap, fatherIndex, lSon);
        fatherIndex = lSon;
      }
    }
    else /*0 sons , I reach a leafe stop the function*/
    {
      return;
    }
  }
  return;
}
/******************************************************************************/
static void BubbleUp(Heap *_heap)
{
  size_t sonIndex = _heap->m_heapSize - 1;
  size_t fatherIndex = (sonIndex - 1) / 2;
  int sonValue, fatherValue;
  VectorGet(_heap->m_vec, fatherIndex, &fatherValue);
  VectorGet(_heap->m_vec, sonIndex, &sonValue);

  while (sonIndex > 0 && (fatherValue < sonValue))
  {
    Swap(_heap, fatherIndex, sonIndex);
    sonIndex = fatherIndex;
    fatherIndex = (sonIndex - 1) / 2;
    VectorGet(_heap->m_vec, fatherIndex, &fatherValue);
    VectorGet(_heap->m_vec, sonIndex, &sonValue);
  }
}
/******************************************************************************/
