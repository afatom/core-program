/******************************************************************************/
/*
static void MaxHeapifyTree(Heap* _heap, size_t _parent)
{
    size_t leftChild, rightChild; 
    leftChild = 2 * _parent;
    rightChild = leftChild +1;

    if(        &&       )  /*check with left son*/

if (&&) /*check with right son*/

    if () /*stop condition - if left is aleaf*/
}

static size_t FindMax
static size_t FindMaxSonIndex(Heap* _heap, size_t _leftSonIndex, size_t _rightSonIndex);

static void shiftup(Heap *_heap, size_t index)
{
    size_t fatherIndex, lSonIndex, rSonIndex;
    void *lSonValue = NULL;
    void *rSonValue = NULL;
    void *fatherValue = NULL;

    fatherIndex = index;
    lSonIndex = fatherIndex * 2;
    rSonIndex = fatherIndex * 2 + 1;

    if (rSonIndex <= _heap->m_heapSize) /*2 sons*/
    {

        VectorGet(_heap->m_vec, lSonIndex, &lSonValue);
        VectorGet(_heap->m_vec, rSonIndex, &rSonValue);

        if (_heap->m_pfLess(lSonValue, fatherValue) == TRUE && _heap->m_pfLess(rSonValue, fatherValue) == TRUE) /*correct heap*/
        {
            return;
        }

        if (_heap->m_pfLess(fatherValue, lSonValue) == TRUE && _heap->m_pfLess(rSonValue, lSonValue) == TRUE) /*swap with the left son*/
        {
            Swap(_heap, fatherIndex, lSonIndex);
            shiftup(_heap, lSonIndex);
        }
        else /*swap with the right son*/
        {
            Swap(_heap, fatherIndex, rSonIndex);
            shiftup(_heap, rSonIndex);
        }
    }
    else if (lSonIndex <= _heap->m_heapSize) /*have 1 son*/
    {
        VectorGet(_heap->m_vec, lSonIndex, &lSonValue);

        if (_heap->m_pfLess(lSonValue, fatherValue) == TRUE) /*correct heap*/
        {
            return;
        }
        if (_heap->m_pfLess(fatherValue, lSonValue) == TRUE) /*swap with the left son*/
        {
            Swap(_heap, fatherIndex, lSonIndex);
            shiftup(_heap, lSonIndex); /*after swap must check sub tree is aheap tree*/
        }
    }
    else /*0 sons , I reach a leafe stop the function*/
    {
        return;
    }
}
static void MaxHeapify(Heap *_heap);

static size_t FindMaxSonIndex(Heap *_heap, size_t _leftSonIndex, size_t _rightSonIndex)
{
    void *elem1 = NULL;
    void *elem2 = NULL;

    VectorGet(_heap->m_vec, _leftSonIndex, &elem1);
    VectorGet(_heap->m_vec, _rightSonIndex, &elem2);
    if (_heap->m_pfLess(elem1, elem2) == TRUE)
    {
        return _rightSonIndex;
    }
    return _leftSonIndex;
}

static size_t FindMaxSonIndex(Heap *_heap, size_t _leftSonIndex, size_t _rightSonIndex);




/*
UNIT(Heap__Peek__Test)
int i=0;
Vector *vec = NULL;
VectorResult res;
Person **arr = NULL;
Person *getPerson = NULL;

const void* peek = NULL;

Heap *heap = NULL;
size_t size=0;

arr = (Person **)malloc(ARR_HUGE_SIZE * sizeof(Person *));
ASSERT_THAT(arr != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    arr[i] = (Person *)malloc(1 * sizeof(Person));
    arr[i]->age = rand() % 80;
}


getPerson = (Person *)malloc(1 * sizeof(Person));

vec = VectorCreate(INITIAL_SIZE, BLOCK_SIZE);
ASSERT_THAT(vec != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((res = VectorAppend(vec, (void *)(arr[i]))) == VECTOR_SUCCESS);
}
ASSERT_THAT(VectorSize(vec) == ARR_HUGE_SIZE);
for (i = 1; i <= ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((res = VectorGet(vec, (size_t)i, (void *)(&getPerson))) == VECTOR_SUCCESS);

}
heap = HeapBuild(vec, Comparator);
ASSERT_THAT(NULL != heap);
size= VectorSize(vec);
AssertHeapMaxProperty(vec, size);

peek = HeapPeek(heap);
VectorGet(vec, 1, (void *)(&getPerson));
ASSERT_THAT(peek == getPerson);

vec = HeapDestroy(&heap);
VectorDestroy(&vec, PersonDestroy);
ASSERT_THAT(NULL == vec);
ASSERT_THAT(NULL == heap);

free(getPerson);

END_UNIT
*/

UNIT(Heap__Extract__Maximum__Test)

int i;
Vector *vec = NULL;
VectorResult res;
Person *arr[ARR_HUGE_SIZE];
puts("291");
Person *getPerson = NULL;
Person *person1 = NULL;
Person *person2 = NULL;
Person *person3 = NULL;
Person *maxPerson = NULL;
Person *heapMaxPerson = NULL;

Heap *heap = NULL;
size_t size;

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    arr[i] = (Person *)malloc(1 * sizeof(Person));
    arr[i]->age = rand() % 80;
}

vec = VectorCreate(INITIAL_SIZE, BLOCK_SIZE);
ASSERT_THAT(vec != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((res = VectorAppend(vec, (void *)(arr[i]))) == VECTOR_SUCCESS);
}
ASSERT_THAT(VectorSize(vec) == ARR_HUGE_SIZE);

VectorGet(vec, ARR_HUGE_SIZE, (void *)(&getPerson));
assert(getPerson != NULL);
assert(getPerson->age != 0);

VectorGet(vec, ARR_HUGE_SIZE - 1, (void *)(&getPerson));
assert(getPerson != NULL);
assert(getPerson->age != 0);

VectorGet(vec, ARR_HUGE_SIZE - 2, (void *)(&getPerson));
assert(getPerson != NULL);
assert(getPerson->age != 0);

size = VectorSize(vec);

heap = HeapBuild(vec, Comparator);
ASSERT_THAT(NULL != heap);

AssertHeapMaxProperty(vec, size);
/*ASSERT_THAT(AssertHeapExtractMaxElement(vec, &maxPerson) == TRUE);
*/
heapMaxPerson = (Person *)(HeapExtract(heap));
ASSERT_THAT(heapMaxPerson != NULL);
ASSERT_THAT(heapMaxPerson == maxPerson);
AssertHeapMaxProperty(vec, size - 1);

vec = HeapDestroy(&heap);

VectorDestroy(&vec, PersonDestroy);
ASSERT_THAT(NULL == vec);
ASSERT_THAT(NULL == heap);

END_UNIT
/*Main function Macro*/

static int AssertHeapExtractMaxElement(Vector *vec, Person **max)
{
    size_t i = 2, size = 0;
    Person *maxperson = NULL;
    Person *person = NULL;
    if (max == NULL)
    {
        return FALSE;
    }
    person = (Person *)malloc(sizeof(Person));
    maxperson = (Person *)malloc(sizeof(Person));

    VectorGet(vec, 1, &maxperson);
    size = VectorSize(vec);
    for (i = 2; i <= size; ++i)
    {
        VectorGet(vec, i, &person);
        if (((Person *)person)->age > ((Person *)maxperson)->age)
        {
            free(person);
            free(maxperson);
            return FALSE;
        }
    }
    free(person);
    free(maxperson);
    VectorGet(vec, 1, *max);
    return TRUE;
}

static void shiftup(Heap *_heap, size_t index)
{
    size_t fatherIndex, lSonIndex, rSonIndex;
    void *lSonValue = NULL;
    void *rSonValue = NULL;
    void *fatherValue = NULL;

    fatherIndex = index;
    lSonIndex = fatherIndex * 2;
    rSonIndex = fatherIndex * 2 + 1;

    VectorGet(_heap->m_vec, fatherIndex, &fatherValue);

    if (rSonIndex <= _heap->m_heapSize) /*2 sons*/
    {

        VectorGet(_heap->m_vec, lSonIndex, &lSonValue);
        VectorGet(_heap->m_vec, rSonIndex, &rSonValue);

        if (_heap->m_pfLess(lSonValue, fatherValue) == TRUE && _heap->m_pfLess(rSonValue, fatherValue) == TRUE) /*correct heap*/
        {
            return;
        }

        if (_heap->m_pfLess(fatherValue, lSonValue) == TRUE && _heap->m_pfLess(rSonValue, lSonValue) == TRUE) /*swap with the left son*/
        {
            Swap(_heap, fatherIndex, lSonIndex);
            shiftup(_heap, lSonIndex);
        }
        else /*swap with the right son*/
        {
            Swap(_heap, fatherIndex, rSonIndex);
            shiftup(_heap, rSonIndex);
        }
    }
    else if (lSonIndex <= _heap->m_heapSize) /*have 1 son*/
    {
        VectorGet(_heap->m_vec, lSonIndex, &lSonValue);

        if (_heap->m_pfLess(lSonValue, fatherValue) == TRUE) /*correct heap*/
        {
            return;
        }
        if (_heap->m_pfLess(fatherValue, lSonValue) == TRUE) /*swap with the left son*/
        {
            Swap(_heap, fatherIndex, lSonIndex);
            shiftup(_heap, lSonIndex); /*after swap must check sub tree is aheap tree*/
        }
    }
    else /*0 sons , I reach a leafe stop the function*/
    {
        return;
    }
}

UNIT(HEAP__Insert__Many__Test)
Heap *heap = NULL;
size_t i = 0;
Person **arr;

Person *first = NULL;
Person *sec = NULL;
Person *third = NULL;
const void *peek = NULL;

Vector *vector = NULL;

first = malloc(sizeof(*first));
sec = malloc(sizeof(*first));
third = malloc(sizeof(*first));

first->age = 130;
sec->age = 135;
third->age = 0;

vector = VectorCreate(VEC_INITIAL_SIZE, VEC_BLOCK_SIZE);
arr = (Person **)malloc(SIZE * sizeof(Person *));
for (i = 0; i < SIZE; ++i)
{
    arr[i] = (Person *)malloc(sizeof(Person));
    arr[i]->age = rand() % 120;
    VectorAppend(vector, arr[i]);
}
ASSERT_THAT(SIZE == VectorSize(vector));
/*PrintForEach(vector, PrintPerson, NULL);*/
heap = HeapBuild(vector, Comparator);
AssertHeapMaxProperty(vector, HeapSize(heap));
/*PrintForEach(vector, PrintPerson, NULL);*/
assert(HeapSize(heap) == SIZE);

HeapInsert(heap, (void *)first);
peek = HeapPeek(heap);
assert(((Person *)peek)->age == 130);
AssertHeapMaxProperty(vector, HeapSize(heap));
/*PrintForEach(vector, PrintPerson, NULL);
*/
HeapInsert(heap, (void *)sec);
peek = HeapPeek(heap);
assert(((Person *)peek)->age == 135);
AssertHeapMaxProperty(vector, HeapSize(heap));

HeapInsert(heap, (void *)third);
peek = HeapPeek(heap);
assert(((Person *)peek)->age == 135);
AssertHeapMaxProperty(vector, HeapSize(heap));

assert(HeapSize(heap) == SIZE + 3);

vector = HeapDestroy(&heap);
VectorDestroy(&vector, PersonDestroy);
free(arr);
ASSERT_THAT(NULL == vector);
ASSERT_THAT(NULL == heap);
free(first);
free(sec);
free(third);

END_UNIT





    int arr[NUM], i;
    Person **prr=NULL;
    prr = (Person**)malloc(NUM * sizeof(Person*)); 
    for (i = 0; i < NUM; ++i)
    {
        arr[i] = i;
    }
    ShuffleArray(arr, NUM);
    for (i = 0; i < NUM; ++i)
    {

        prr[i] =(Person*) malloc(sizeof(Person));
        prr[i]->m_age = i;
    }


    vec = VectorCreate(INITIAL_SIZE, BLOCK_SIZE);
    ASSERT_THAT(vec != NULL);
    for (i = 0; i < NUM; ++i)
    {
       ASSERT_THAT( VectorAppend(vec, (void *)prr[arr[i]]) == VECTOR_SUCCESS);
    }

	
    for (i = 1; i < NUM; ++i)
    {
        ASSERT_THAT(VectorGet(vec, (size_t)i,&pvalue) == VECTOR_SUCCESS);
        printf("Person at [%d] AGE %d\n", ((Person*)pvalue)->m_age,((Person*)pvalue)->m_edu );
    }

    heap = HeapBuild(vec, Comparator);
    ASSERT_THAT(NULL != heap);

/*
    for (i = 0; i < NUM; ++i)
    {
        puts("146");
        ASSERT_THAT(HeapInsert(heap, (void *)prr[arr[i]]) == HEAP_SUCCESS);
    }*/

    /*counter =  HeapSize(heap);*/
    /*ASSERT_THAT(counter == NUM);*/
    /*con = NORMALL;*/
    HeapForEach(heap, HeapPrint, NULL);
    /*ASSERT_THAT(counter == NUM);
    */
   
    vec = HeapDestroy(&heap);
    VectorDestroy(&vec, NULL);
    for (i = 0; i < NUM; ++i)
    {
        free(prr[i]);
    }
    free(prr);
    ASSERT_THAT(NULL == heap);
    ASSERT_THAT(vec==NULL);







