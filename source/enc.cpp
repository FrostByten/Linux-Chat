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
-- INTERFACE: void encrypt_text(char *buffer, int len, char *key, int k_len, char *key2, int k2_len)
--
-- PARAMETERS:	char *buffer:		The data to apply the encyption to
--				int len:		The length of the buffer
--				char *key:		The data of the first key
--				int k_len:			The length of the first key
--				char *_key2:	The data of the second key
--				int k2_len:		The length of the second key
--
-- RETURNS: void.
--
-- NOTES:
-- Encrypts the data given.
----------------------------------------------------------------------------------------------------------------------*/
void enc::encrypt_text(char *buffer, int len, char *key, int k_len, char *_key2, int k2_len)
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
        k2 += _key2[i];
    k1 /= k_len;
    k2 /= k2_len;
    }

    k2 = ((k2 << 3) | k2 >> (32 - 3));

    for(i = 0; i < len; ++i)
        buffer[i] ^= i%2==0?k1:k2;
}

