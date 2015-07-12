#include <stdio.h>
#include <string.h>
#include "crypt.h"
#include "s_DES.h"
#include "key_gen.h"

/*	USAGE: sdes <FLAG> <input filename> <output filename> <seed(base2)> 
* 	FLAGS:	-d: decrypt
*			-e: encrypt
*/
int main(int argc, char* argv[])
{
	/*DECLARATIONS*/
	char usage[] = "sdes by Jason Giancono\nUSAGE: sdes <FLAG> <input filename> <output filename> <seed key (in base 2)>\nFLAGS:\t\t-d: decrypt\n\t\t-e: encrypt\n";
	if (argc != 5)
		printf("%s", usage);
	else
	{
		unsigned short seedkey, kOne, kTwo, ii, error;
		FILE *output, *input;
		char temp;
		error = 0;
		/*turning the char array into a (short) int*/
		seedkey = 0;
		for (ii=0;ii<10;ii++)
		{
			if (argv[4][ii] == '1')
			{
				seedkey += powerOf2(9-ii);
			}
		}
		/*calculate the two subkeys*/
		keygen(seedkey, &kOne, &kTwo);
		/*opening files for read/writing, check for errors*/
		input = fopen(argv[2], "r");
		if ( (input != 0) && (( output = fopen(argv[3], "w") ) != 0))
		{
			/*am I encrypting or decrypting (changes key order)*/
			if (!strcmp(argv[1], "-e"))
			{
				printf("\n-----\nEncoding\n-----\n");
				/*continue until error or EOF*/
				while ((feof(input) == 0) && (ferror(input) == 0) && (ferror(output) == 0))
				{
					/*encrypt using S-DES with the two keys*/
					temp = (char)(encryptDecrypt(fgetc(input), kOne, kTwo));
					/*write it to file (unless it was EOF)*/
					if(feof(input) == 0)
						fputc(temp, output);
				}
			}
			else if(!strcmp(argv[1], "-d"))
			{
				printf("\n-----\nDecoding\n-----\n");
				/*continue until error or EOF*/
				while ((feof(input) == 0) && (ferror(input) == 0) && (ferror(output) == 0))
				{
					/*decrypt using S-DES with the two keys backwards*/
					temp = (char)(encryptDecrypt(fgetc(input), kTwo, kOne));
					/*write it to file (unless it is EOF)*/
					if(feof(input) == 0)
						fputc(temp, output);
				}
			}
			else printf("%s", usage);
			printf("\n-----\nDone\n-----\n");
		}
		else 
		{
			error = 1;
			printf("%s", usage);
		}
		/*print errors*/
		if ((error == 1) || (ferror(input) != 0) || (ferror(output) != 0))
			perror("A read/write error occurred");
		/*close files (if they were open)*/
		if(output != 0) 
			fclose(output);
		if(input != 0)
			fclose(input);
	}
	return 0;
}
