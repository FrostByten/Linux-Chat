#ifndef SHARED_H
#define SHARED_H
typedef enum message_type
{
CONNECTION = 0x11, CHAT, NAME_CHANGE, DISCONNECTION, WHISPER, DEAD_CONNECTION
} message_type;
#endif
