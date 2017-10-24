#include "crypt.h"
#include "s_DES.h"
#include <stdio.h>

/*switch kOne with kTwo to decrypt*/
unsigned short encryptDecrypt(unsigned short input, unsigned short kOne, unsigned short kTwo)
{
	input = initialP(input);		/*IP*/
	input = fK(input, kOne);		/*fK1*/
	input = switch_a_roo(input);	/*SW*/
	input = fK(input, kTwo);		/*fK2*/
	input = inverseP(input);		/*Inverse IP*/
	return input;
}

unsigned short initialP(unsigned short input)
{
	unsigned short postIP;
	/*load permutation into memory*/
	int iPBox[8] = {2,6,3,1,4,8,5,7};
	/*permute!*/
	postIP = permute(input, iPBox, 8, 8);
	return postIP;
}

unsigned short inverseP(unsigned short input)
{
	unsigned short postIP;
	/*load permutation into memory*/
	int iPBox[8] =  {4,1,3,5,7,2,8,6};
	/*permute!*/
	postIP = permute(input, iPBox, 8, 8);
	return postIP;
}

unsigned short fK(unsigned short input, unsigned short key)
{
	return ( ( (input >> 4) ^ fFunction(input & 15, key) ) << 4) + (input & 15); 
	/*	this is the Fk function
		fK(L, R) = (L ^ F(R, SK), R)
	*/
}

unsigned short fFunction(unsigned short r, unsigned short key)
{
	/*fFunction because one letter function are bad... apparently*/
	/*load s-boxes into memory*/
	int sZero[4][4] = {	{1,0,3,2},
						{3,2,1,0},
						{0,2,1,3},
						{3,1,3,2}	};
						
	int sOne[4][4] = {	{0,1,2,3},
						{2,0,1,3},
						{3,0,1,0},
						{2,1,0,3}
									};
	/*load permutations into memory*/
	int eP[8] = {4,1,2,3,2,3,4,1};
	int pFour[4] = {2,4,3,1};
	/*value for expanded/permuted r*/								
	unsigned short expR; 
	expR = permute(r, eP, 4, 8);
	/*XOR with the subkey*/
	expR = expR ^ key;
	/*convert the bits to coordinates using bitshift magic then retrieve new values from s-box*/
	expR = ( sZero[ (( expR & 128) >> 6) + (( expR & 16) >> 4)][ ((expR & 64) >> 5) + ((expR & 32) >> 5) ] << 2 ) + sOne[ (( expR & 8) >> 2) + ( expR & 1) ][ (( expR & 4) >> 1) + (( expR & 2) >> 1) ];
	/*P4*/	
	expR = permute(expR, pFour, 4, 4);
	return expR; 
}

unsigned short switch_a_roo(unsigned short input) /* because switch is a reserved word */
{
	/*input shifted right 4 bits + input with first 4 bits masked to 0 shifted left 4 bits*/
	return ( (input >> 4) + ((input & 15) << 4) );
}
