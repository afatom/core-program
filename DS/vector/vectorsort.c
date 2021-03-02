#include "vector.h"
#include "vectorsort.h"
#include "ADTDefs.h"
#include <stdlib.h>

/******************************************************************************/
ADTErr InsertionSort(Vector* _vec)
{
  int after, before;
  size_t  _numOfItems,i,j;
  if(NULL == _vec)
  {
    return ERR_NOT_INITIALIZED;
  }
  VectorItemsNum(_vec, &_numOfItems);
  for(i = 0; i < _numOfItems ; ++i)
  {
  	for(j = i; j > 0 ; --j)
  	{
      VectorGet(_vec, j,&after);
  		VectorGet(_vec, j-1,&before);
		  if(after < before)
      	{
      		VectorSet(_vec, j, before);
        	VectorSet(_vec, j-1, after);
      	}
  	}
  }
  return ERR_OK;
}

/******************************************************************************/
