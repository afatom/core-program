#ifndef _HASH_H_
#define _HASH_H_
#include "ADTDefs.h"
#include <stddef.h>     /*size_t*/

typedef struct Hash Hash;

Hash* HashCreate(size_t _size);

void HashDestroy(Hash* _hash);

ADTErr HashInsert(Hash* _hash, int _data);

ADTErr HashRemove(Hash* _hash, int _data);

int HashIsFound(const Hash* _hash, int _data);

size_t HashNumOfItems(const Hash* _hash);

size_t HashCapacity(const Hash* _hash);

double HashAverageCollisions(const Hash* _hash);

size_t HashMaxCollisions(const Hash* _hash);

void HashPrint(const Hash* _hash);

#endif /*_HASH_H_*/