#include "bst.h"
#include <stdio.h> 		/*printf*/
#include <stdlib.h>		/*malloc*/
#include "ADTDefs.h"



int main ()
{
  Tree* tree;
  tree =	TreeCreate();
  TreeTraverse x =POST_ORDER;
  //Tree *tree;
  int i;
  //tree = TreeCreate();
  
  for (i = 100; i > 0; --i)
  {
    TreeInsert(tree, i);
  }
  TreePrint(tree, x);
  //TreeDestroy(tree);

  return 0;
}
