#include "key_gen.h"
#include "crypt.h"
/*this function takes a seed and pointers to memory (sizeof(unsigned short)) and generates both keys*/
void keygen(unsigned short seed, unsigned short* kOne, unsigned short* kTwo)
{
	*kOne = pTen(seed);		/*P10*/
	*kOne = lSOne(*kOne); 	/*LS1*/
	*kTwo = *kOne;			/*copy kOne to make kTwo*/
	*kOne = pEight(*kOne);	/*P8 (this is subkey 1)*/
	*kTwo = lSOne(*kTwo);	/*LS1 another 2 times*/
	*kTwo = lSOne(*kTwo);
	*kTwo = pEight(*kTwo);	/*P8 to get subkey 2*/
}

unsigned short pTen(unsigned short seed)
{
	/*gives out the key after P10*/
	unsigned short postPTen;
	/*loading the permutation in memory*/
	int pTenBox[10] = {3,5,2,7,4,10,1,9,8,6};
	postPTen = permute(seed, pTenBox, 10, 10);
	return postPTen;
}

unsigned short lSOne(unsigned short key)
{
	/*splits the key, does left circular shift on both then re-joins*/
	/*31(10) = 0000011111(2) (masks left side to 0)*/
	unsigned short tempKeyRight = (key & 31); 
	/*shift down 5 to isolate left 5 bits*/
	unsigned short tempKeyLeft = (key >> 5);
	/*left shifting*/
	tempKeyRight = tempKeyRight << 1;
	tempKeyLeft = tempKeyLeft << 1;
	/*making that pesky left-most bit come around*/
	if ( (tempKeyRight & 32) == 32 )
		tempKeyRight = tempKeyRight - 31;
	if ( (tempKeyLeft & 32) == 32 )
		tempKeyLeft = tempKeyLeft - 31;
	/*rejoining the left and right side*/
	return ( tempKeyRight + (tempKeyLeft << 5) );
}

unsigned short pEight(unsigned short key)
{
	/*gives out the key after P8*/
	unsigned short postPEight;
	/*loading permutation into memory*/
	int pEightBox[8] = {6,3,7,4,8,5,10,9};
	postPEight = permute(key, pEightBox,10, 8);
	return postPEight;
}
