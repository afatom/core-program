#include <stdio.h>
#include <ctype.h>

#define MAX_WORD_SIZE 100 /*max size*/
#define INITIAL_FILE_SIZE 1000 

typedef struct Word {
	char* str[INITIAL_FILE_SIZE];
	int* freqArr[INITIAL_FILE_SIZE]={0};
} Word;

int CountLetters(const char* _destFileName)
{
	char letter; 
	int ch;
	FILE* fp;
	int lcCounterArray[26]={0};
	int ucCounterArray[26]={0};

	fp = fopen(_destFileName, "r+");
	if (NULL == fp)
	{
		return -1;
	}
	fseek(fp,0,0);
	while(!feof(fp))
	{
		ch = fgetc(fp);
		if (isalpha(ch))
		{
			if(islower(ch)) /*lower case*/
			{
				++lcCounterArray[ch-'a'];
			}
			/*upper case*/
			++ucCounterArray[ch-'A'];
		}
	}
	fclose(fp);
	
	printf("Lower case arr\n");
	for (int i=0; i<26; ++i)
	{
		letter = i+'a';
		printf("letter %c  appears %d times\n", letter,lcCounterArray[i]);
	}
	
	printf("Upper case arr\n");
	for (int i=0; i<26; ++i)
	{
		letter = i+'A';
		printf("letter %c  appears %d times\n", letter,ucCounterArray[i]);
	}
	
	return 0;
}

/*************************************************************************************/
int AddMemory(Word* ptr)
{
	int* tempCounterArr = NULL;
	char** tempStrArr = NULL;
	/*first realloc*/
	tempCounterArr = (int*)realloc(ptr->freqArr, (INITIAL_FILE_SIZE * 2) * sizeof(int));
	if (NULL == tempCounterArr)
	{
		return 1; /*realloc failure*/
	}
	
	tempStrArr = (char**)realloc(ptr->str, (INITIAL_FILE_SIZE * 2) * sizeof(char*));
	if (NULL == tempStrArr)
	{
		free(tempCounterArr);
		return 1;
	}
	
	ptr->str = tempStrArr;
	ptr->freqArr = tempCounterArr;
	return 0;
}
/**************************************************************************************/

int CountWords(const char* _destFileName)
{
	char letter; 
	int ch;
	FILE* fp;
	char tempStr[MAX_WORD_SIZE];
	Word* wordPtr = NULL;
	wordPtr = (Word*)malloc(INITIAL_FILE_SIZE * sizeof(Word));
	if (NULL == wordPtr)
	{
		return 1; /*memory failure*/
	}
	
	fp = fopen(_destFileName, "r+");
	if (NULL == fp)
	{
		return -1;
	}
	fseek(fp,0,0);
	int i =0; int counter =0;
	while(!feof(fp))
	{
		fscanf(fp, "%MAX_WORD_SIZEs ", tmpStr);
		++counter;
		//++wordPtr->freqArr[i];
		/*check duplicates*/
		for (int i=0; i < counter; ++i)
		{
			if (!strcmp ( wordPtr->str[i], tempStr))
			{
				++wordPtr->freqArr[i];
			}
		}
		if (counter==INITIAL_FILE_SIZE)
		{
			/*add memory*/
		}
	}
	fclose(fp);
	

	
	return 0;
}

int main ()
{
	int res = CountLetters("person.txt");

return 0;
}
