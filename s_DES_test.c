#include "crypt.h"
#include "s_DES.h"
#include "key_gen.h"
#include <stdio.h>
void test(unsigned short input, unsigned short expOutput, unsigned short key, char type);

int main()
{
	/*expected output has been pre-calculated*/
	printf("====RUNNING S-DES TESTS====\n\n");
	/*key 0111100110 */
	/*input 10010110 */
	/*expOutput should encrypt to 10001100 */
	test(150,140,486,'e');

	/*key 0100101100 */
	/*input 11010011 */
	/*expOutput should encrypt to 00010000 */
	test(211,16,300,'e');

	/*key 0111100110 */
	/*input 10001100 */
	/*expOutput should encrypt to 10010110 */
	test(140,150,486,'d');

	/*key 0100101100 */
	/*input 00010000 */
	/*expOutput should encrypt to 11010011 */
	test(16,211,300,'d');
	return 0;
}

void test(unsigned short input, unsigned short expOutput, unsigned short key, char type)
{
	unsigned short a,b,output;
	static int testNo = 0;
	static int testPassNo = 0;
	testNo++;
	printf("\nTEST %d ", testNo);
	if (type == 'e')
	{
		printf("ENCRYPTION:\t");
		keygen(key, &a,&b);
	}
	else 
	{
		printf("DECRYPTION:\t");
		keygen(key, &b,&a);
	}
	output = encryptDecrypt(input,a,b);
	printf("\n----------\nGrade:\t\t\t");
	if (output == expOutput)
	{
		printf("\033[22;1;32mPASS\033[0m\n");
		testPassNo++;		
	}
	else printf("\033[22;1;31mFAIL\033[0m\n");
	printf("Input:\t\t\t");
	printBin(input,8);
	printf("\nKey:\t\t\t");
	printBin(key,10);
	printf("\nExpected Output:\t");
	printBin(expOutput,8);
	printf("\nActual Output:\t\t");
	printBin(output,8);
	printf("\n---------\n\033[22;1;32m%d/%d passed\033[0m\n",testPassNo,testNo);
}
