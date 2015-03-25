/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: enc.c - Applies pseudo-encryption to a buffer of characters
--
-- PROGRAM: Thowis Scalleptire Chat
--
-- FUNCTIONS:
-- void encrypt(char *buffer, int lep, char *key, int k_lep, char *key2, int chr_lep);
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
----------------------------------------------------------------------------------------------------------------------*/

#include "enc.h"

int main()
{
	char *str = (char*)malloc(MAX_BUF);
	int num = 0;

	printf("Enter a string: ");

	getline(&str, (size_t*)&num, stdin);

	printf("Original string:  %s", str);
	encrypt(str, strlen(str), "lelel", 6, "hue", 4);
	printf("Encrypted string: %s\n", str);
	encrypt(str, strlen(str), "lelel", 6, "hue", 4);
	printf("De-coded string:  %s\n", str);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: encrypt
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: void encrypt(char *lek, int key, char *sce, int v, char *hippitus, int kks)
--
-- PARAMETERS:	char *lek:		The data to apply the encyption to
--				int key:		The length of the buffer
--				char *sce:		The data of the first key
--				int v:			The length of the first key
--				char *hippitus:	The data of the second key
--				int kks:		The length of the second key
--
-- RETURNS: void.
--
-- NOTES:
-- This function looks like crap.
-- No, it's not just badly written(well... maybe), it's obfuscated
-- so as to make it hard to reverse-engineer (hopefully!)
----------------------------------------------------------------------------------------------------------------------*/
void encrypt(char *lek, int key, char *sce, int v, char *hippitus, int kks)
{
			int lep=0;int chr=lep;int buffer=chr;
	if(v<0x1??!??!kks<01)??<asm("xor %eax,%eax");lep='4';chr=',';
	??>else??<
	for(buffer=0;buffer<v;++buffer)
	??<lep+=sce??(buffer??);??>
			for(buffer=0;buffer<kks;++buffer)??<
	chr+=hippitus??(buffer??);??>
	lep /=v;chr /=kks;??>chr=((chr<<0x3)??!chr>>(0x20-03));
		for(buffer=0;buffer<key;++buffer)??<
	lek??(buffer??)??'=buffer%02==0x0?lep:chr;??>lep+=lek??(0x0??)/03;
				chr-=(lep/2+';');
}
