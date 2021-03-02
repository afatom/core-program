#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef int (*PersonDuty)(char*) ;

struct person {
	char*	 name;
	int	 age;
   	PersonDuty	func;
	
};
typedef struct person Person_t;

int Refua(char* name)   { printf("I'm a doctor\n");		return 0; }
int Handasa(char* name) { printf("I'm an engineer\n");  return 0; }
int Pilot(char* name) { printf("I'm a pilot\n");  return 0; }

typedef struct familyTree {
   	 int nMembers;
   	 Person_t p[2];
   	 struct familyTree* 	next;
}FamilyTree_t;


FamilyTree_t Halakhmi = { 2, "Ilan", 28, Refua,"Gilad", 26, Handasa, NULL};
FamilyTree_t Buchler  = { 2, "Rita", 38, Refua,"Brian", 30, Handasa, NULL };

void DoIt(FamilyTree_t* ftPtr, char* name) 
{
	for (int i =0; i<ftpr->nMembers; ++i)
	{
		if(!(strcmp(name,ftPtr->p[ftpr->nMembers].func(name))))
		{
			return;
		}
	}
	printf("Family Member Not Found!\n");
}

int main() {
	DoIt(&Halakhmi , "Gilad");
	//DoIt(&Buchler  , "Rita");
	return 1;
}


