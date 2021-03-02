
#ifndef _LIST_H_
#define _LIST_H_

typedef struct Person Person;
struct Person {
    int     m_id; /* Unique Key for sorting*/
    char    m_name[128];
    int     m_age;
    Person* m_next;
};


/*******************************************************************************
*[Description]:Creating And Inserting new heads or NODES Datat Structure. 
*Insertion will can be at any place in the list. 
*[Input]:Pointer to Person struct (person left to me) and pointer _p to points 
*to NEXT Person.  
*[output]:Pointer wich points to next person 
*[Errors]:
*******************************************************************************/
Person* ListInsertHead(Person* _head, Person* _p);

/*******************************************************************************
*[Description]:Deleting One person or NODES Datat Structure.  
*[Input]:Pointer to Person struct (person left to me) and pointer _p to points 
*to NEXT Person.  
*[output]:Pointer wich points to next person 
*[Errors]:
*******************************************************************************/
Person* ListRemoveHead(Person* _head, Person** _item);

/*******************************************************************************
*[Description]:Insert sorted by input Key. standard insertion.
*[Input]:pointer to whole data (head), key, and pointer to new person that i 
*want to add.  
*[output]:updated head pointer.
*[Errors]:
*******************************************************************************/
Person* ListInsertByKey(Person* _head, int _key, Person* _p);

/*******************************************************************************
*[Description]:Insert sorted by input Key. recursion insertion.
*[Input]:pointer to whole data (head), key, and pointer to new person that i 
*want to add.  
*[output]:updated head pointer.
*[Errors]:
*******************************************************************************/
Person* ListInsertByKeyRec(Person* _head,  int _key, Person* _p);

/*******************************************************************************
*[Description]:Remove by input Key. standard deleting.
*[Input]:pointer to whole data (head), key, and pointer to the person pointer 
*that i want to delete.  
*[output]:updated head pointer.
*[Errors]:
*******************************************************************************/
Person* ListRemoveByKey(Person* _head, int _key, Person** _p);

/*******************************************************************************
*[Description]:Remove by input Key. Remove by recursion deleting.
*[Input]:pointer to whole data (head), key, and pointer to the person pointer 
*that i want to delete.  
*[output]:updated head pointer.
*[Errors]:
*******************************************************************************/
Person* ListRemoveByKeyRec(Person* _head,  int _key, Person** _p);

/*******************************************************************************
*[Description]:Printing persons data.
*[Input]:pointer to whole data (head).
*[output]:Void
*[Errors]:
*******************************************************************************/
void    PrintList(Person* _head);

/******************/
#endif /*_LIST_H_*/


