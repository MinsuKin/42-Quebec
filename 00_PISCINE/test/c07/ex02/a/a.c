#include <stdio.h>

void init_ptr(int **pPtr)
{
	*pPtr = 0;
}

int main()
{
	int *ptr;
	printf("ptr = %d\n", ptr);

	init_ptr(&ptr);
	printf("ptr = %d\n", ptr);
}
