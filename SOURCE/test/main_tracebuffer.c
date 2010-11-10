#include "tracebuffer.h"
#include "test_tracebuffer.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Starting \n");
	int i, j;

	printf("TESTING TRACEBUFFERS\n\n");

	// Initializing tracebuffer
	k_tracebuffer_ptr TB = malloc(sizeof(k_tracebuffer));
	
	printf("Print Empty Tracebuffer\n");
	test_tracebuffer_print(TB);
	
	printf("Test update tracebuffer\n\n");
	for(i=0; i<32; i++)
	{
		k_tracebuffer_update(i, i+10, i+20, TB);
		if (i%2 == 0)
			test_tracebuffer_print(TB);
	}
	
	printf("DONE\n");
}
