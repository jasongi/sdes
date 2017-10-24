#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "key_gen.h"
#include "crypt.h"
void test(unsigned short seed, unsigned short eKOne, unsigned short eKTwo);
int main()
{
	/*expected output has been pre-calculated*/

	printf("====RUNNING KEYGEN TESTS====\n\n");
	/*	seed: 			1010000010
	*	expected k1:	10100100
	*	expected k2:	01000011	*/
	test(642, 164, 67);

	/*	seed: 			1001010010
	*	expected k1:	10110001
	*	expected k2:	00100011	*/
	test(594, 177, 35);

	/*	seed: 			0000111101
	*	expected k1:	01001011
	*	expected k2:	10111000	*/
	test(61, 75, 184);

	/*	seed: 			1111011111
	*	expected k1:	11111111
	*	expected k2:	11101111	*/
	test(991, 255, 239);

	return 0;
}

void test(unsigned short seed, unsigned short eKOne, unsigned short eKTwo)
{
	unsigned short kOne, kTwo;
	static int testNo = 0;
	static int testPassNo = 0;
	testNo++;
	printf("\nTEST %d", testNo);
	printf("\n----------\nGrade:\t\t");
	keygen(seed, &kOne, &kTwo);
	if ( (kOne == eKOne) && (kTwo == eKTwo) )
		{
			printf("\033[22;1;32mPASS\033[0m\n");
			testPassNo++;
		}
	else printf("\033[22;1;31mFAIL\033[0m\n");
	printf("Seed:\t\t");
	printBin(seed,10);
	printf("\nExpected Key 1:\t");
	printBin(eKOne,8);
	printf("\nKey 1:\t\t");
	printBin(kOne,8);
	printf("\nExpected Key 2:\t");
	printBin(eKTwo,8);
	printf("\nKey 2:\t\t");
	printBin(kTwo,8);
	printf("\n---------\n\033[22;1;32m%d/%d passed\033[0m\n",testPassNo,testNo);
}
