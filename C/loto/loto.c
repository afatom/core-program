#include "loto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int CheckIfExist(size_t *arr, size_t size, size_t num)
{
	int i;
	for(i = 0; i < size; ++i)
	{
		if(arr[i] == num)
		{
			return 1; /*Exist*/
		}
	}
	return 0;
}
 
size_t NumbersLottery(size_t size) 
{

    size_t res;
    srand((unsigned int)time(NULL));
    res = rand()%(size);
	return res;
}



void ArrayFill(char *arr, size_t raw, size_t col)
{
	int r, c; int counter =0;
	size_t num = NumbersLottery(49);
    while (counter < 6)
    {
    	num = NumbersLottery(49);
		for(r = 0; r < raw ; ++r)
		{
		    for(c = 1; c < col+1 ; ++c)
		    {
		        if ((c+r*10) == num && (*(arr + c + col*r) != '*'))
		        {
		            *(arr + c + col*r) = '*';
		            ++counter;  
		        }
		        
		        else
		        {
		            if (*(arr + c + r * col) != '*')
		            {
		                *(arr + c + r * col) = '-';
		            }
		        }
		        
		    }
		}
	}
}


//void ArrayFill(char *arr, size_t raw, size_t col, size_t num)

void printarr(char *arr, size_t raw, size_t col)
{
    printf(" ");
    for (int j =1; j<col+1;++j)
    {
        printf("%d ",j);
    }
    printf("\n");
    int r, c;
    for (r = 0; r < raw ; ++r)
    {
    	printf("%d",r);
        for (c = 1; c < col+1; ++c)
        {
            printf("%c ", *(arr + c + r * col));
        }
        printf("\n");
    }
}

int printToFile(char *arr, size_t raw, size_t col, const char *filename)
{
    FILE* fp = fopen(filename,"a+");
    if (NULL == fp)
    {
        return 1; /*failure*/
    }
    fprintf(fp," ");
    for (int j =1; j<col+1;++j)
    {
        fprintf(fp,"%d ",j);
    }
    fprintf(fp,"\n");

    int r, c;
    for (r = 0; r < raw; ++r)
    {
        fprintf(fp,"%d",r);
        for (c = 1; c < col+1; ++c)
        {
            fprintf(fp, "%c ", *(arr + c + r * col));
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;
}
