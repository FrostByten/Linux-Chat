#include "enc.h"

/*int main()
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
}*/

int encrypt(char *buffer, int len, char *key, int k_len, char *key2, int k2_len)
{
	int k1 = 0;
	int k2 = 0;
	int i = 0;

	if(k_len < 1 || k2_len < 1)
	{
		k1 = '4';
		k2 = ',';
	}
	else
	{
	for(i = 0; i < k_len; ++i)
		k1 += key[i];
	for(i = 0; i < k2_len; ++i)
		k2 += key2[i];
	k1 /= k_len;
	k2 /= k2_len;
	}

	k2 = ((k2 << 3) | k2 >> (32 - 3));

	for(i = 0; i < len; ++i)
		buffer[i] ^= i%2==0?k1:k2;
}
