/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: shared.c - Defines protocol-specific values
--
-- PROGRAM: Thowis Scallentire Chat
--
-- FUNCTIONS:
--	none.
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
----------------------------------------------------------------------------------------------------------------------*/

#ifndef SHARED_H
#define SHARED_H

typedef enum message_type
{
	CONNECTION = 0x11, CHAT, NAME_CHANGE, DISCONNECTION, WHISPER
} message_type; 

#endif
