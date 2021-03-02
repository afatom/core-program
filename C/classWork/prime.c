#include <stdio.h>
#include <math.h>
int IsPrimeNumber (int Num)
{
	double result;
	/*return*/
	if (Num < 1)
	{
		/*invalid input*/
		return 1;
	}
	result = sqrt(Num);
	for (int i=2; i< (int)result; ++i)
	{
		if (Num%i==0)
		{
			return 2;
		}
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	int result;
	result = IsPrimeNumber(23);
	printf ("%d\n", result);

	return 0;
}
