#include "list.h"
#include <stdio.h>      /*printf*/
#include <stdlib.h>     /*malloc*/
#include <string.h>


Person* CreatePerson(int id, const char *str, int age)
{
    Person* ptr = NULL; 
    ptr = (Person*)malloc(sizeof(Person));
    if (NULL == ptr)
    {
        return NULL;
    }
    ptr->m_id = id;
    ptr->m_age = age;
    strcpy(ptr->m_name, str);
    ptr->m_next = NULL;
    return ptr; 
}



int main (int argc, char* argv[])
{
    Person* head = NULL;
    

    Person* p1 = CreatePerson(125,"Adva", 32);
    Person* p2 = CreatePerson(289,"niko", 33);
    Person* p3 = CreatePerson(5,"rambo", 32);
    Person* p4 = CreatePerson(4,"zoro", 33);
    Person* p5 = CreatePerson(3,"foo", 33);
    Person *p6 = CreatePerson(100, "flop", 33);
    Person *p7 = CreatePerson(17, "Adham", 32);
    Person *p8 = CreatePerson(7, "Ger", 33);
    Person *p9 = CreatePerson(11, "axel", 32);
    Person *p10 = CreatePerson(9, "slash", 33);
    Person *p11 = CreatePerson(19, "davvv", 33);
    Person *p12 = CreatePerson(99, "era", 33);

    Person *p13 = CreatePerson(0, "Deleted", 0);
    Person *pdel = p13;

	//head = ListInsertHead(head, p1);
	//head = ListInsertHead(head, p2);
	//head = ListInsertHead(head, p3);
	//PrintList(head);
	//head = ListRemoveHead(head, &pdel);
	/*
    head = ListInsertByKey(head, 125 ,p1);
    head = ListInsertByKey(head, 289, p2);
    head = ListInsertByKey(head, 5, p3);
    head = ListInsertByKey(head, 100, p6);
    head = ListInsertByKey(head, 17, p7);
    */
	puts("**************");
	PrintList(head);
	head = ListInsertByKeyRec(head, 125, p1);
	head = ListInsertByKeyRec(head, 289, p2);
	head = ListInsertByKeyRec(head, 5, p3);
	head = ListInsertByKeyRec(head, 100, p6);
		puts("**************");
	PrintList(head);
	/*
    head = ListInsertByKey(head, 1, p4);
    head = ListInsertByKey(head, 1, p5);
    head = ListInsertByKey(head, 1, p6);
    head = ListInsertByKey(head, 1, p7);
    head = ListInsertByKey(head, 1, p8);
    head = ListInsertByKey(head, 1, p9);
    head = ListInsertByKey(head, 1, p10);
    head = ListInsertByKey(head, 1, p11);
    head = ListInsertByKey(head, 1, p12);

    PrintList(head);
    printf("\n________________________________________\n");
    head = ListRemoveByKeyRec(head, 17, &pdel);
    printf("\n________________________________________\n");

    PrintList(head);

    //head = ListRemoveHead(head, &pdel);
    //printf("\n________________________________________\n");
    //PrintList(head);
	*/
    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);

    free(p6);
    free(p7);
    free(p8);
    free(p9);
    free(p10);
    
    free(p11);
    free(p12);
    free(p13);

    return 0;
}
