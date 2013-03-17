#include <stdio.h>
#define N_LENGTH 10


void next_name(char* str)
{
	int c;

	c = N_LENGTH-1;
	str[c]++;
	while (str[c] > 'C') 
	{
		str[c]='A';
		c--;
		str[c]++;
	}
}

main()
{
	char name[N_LENGTH+1];
	int i, j;
	int c = N_LENGTH-1;
	// initialise name array
	for (i = 0; i<N_LENGTH; i++) 
	{
		name[i] = 'A';
	}
	// test loop
	for (j = 0; j<30; j++) 
	{
		printf("%s\n", name);
		next_name(name);
	}
	return 0;
}
