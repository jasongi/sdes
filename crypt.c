#include <stdio.h>
#include "crypt.h"

/* generic function for doing permutation. We only care about the last <inputLen> bits in
 * the input and the permutation array is of length <outputLen>.
 */
unsigned short permute(unsigned short input, int* permutation,int inputLen, int outputLen)
{
	int ii;
	unsigned short output = 0;
	unsigned short cursor;
	for(ii=1;ii<=outputLen;ii++)
	{
		/*	set cursor to mask all bits except the one specified
		*	in the permutation array */
		cursor = powerOf2(inputLen-permutation[ii-1]);
		if ( (cursor & input) == cursor )
		{
			/*if the bit in that pos is one, add it, otherwise don't worry*/
			output += powerOf2(outputLen-ii); 
		}
	}
	return output;
}

/*returns 2 to the power of the imported exponent*/
unsigned short powerOf2(unsigned short exponent)
{
	int ii;
	unsigned short retVal = 1;
	for (ii=0;ii<exponent;ii++)
		retVal = retVal*2;
	return retVal;
}

/*	prints out a number in base two, given the number and it's length (in bits)
 *	only really used in tests*/
void printBin(unsigned short bin, int bitNum)
{
	int ii;
	for(ii=(bitNum-1); ii>=0;ii--)
	{
		if( ( bin & powerOf2(ii) ) > 0)
			printf("1");
		else
			printf("0");
	}
}
