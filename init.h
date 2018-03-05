// standard library import
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// for boolean ( true == 0 ) ( false == 1 )
#define true 0
#define false 1

// file initialize
FILE *fobj;

// STARTUP CHECK METHOD ( FOR CHECK THE NECESSARY FILE EXISTS OR NOT ) :: void
void checkFileExists()
{
	fobj = fopen("fs//items.txt", "r");
	
	if (fobj == 0)
	{
		printf("\n#PROGRAM : File #items.txt doesn't exists, creating file...");
		fopen("fs//items.txt", "a+");
	}
	fclose(fobj);
	
	fobj = fopen("fs//receipt.txt", "r");
	if (fobj == 0)
	{
		printf("\n#PROGRAM : File #receipt.txt doesn't exists, creating file...");
		fopen("fs//receipt.txt", "a+");
	}
	fclose(fobj);
	printf("\n#PROGRAM : File initalize sucessfully.");
}
