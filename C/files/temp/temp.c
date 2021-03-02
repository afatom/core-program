#include <stdio.h>


int main (){
FILE* fp = fopen("file1.txt", "r+");
//printf("enter string\n");
char str[25];
int res = fscanf(fp,"%s", str);
printf("res = %d", res);
return 0;
}
