/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: enc.h - Applies pseudo-encryption to a buffer of characters
--
-- PROGRAM: Thowis Scallentire Chat
--
-- FUNCTIONS:
-- void encrypt(char *buffer, int len, char *key, int k_len, char *key2, int k2_len);
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
----------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 256
#define CHAR_BITS 8

void encrypt(char*, int, char*, int, char*, int); 
