#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_PROTOCOL_NAME_SIZE 16

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned long u_long;

typedef union
{
	u_short short_val;
	u_char char_val[2];
} u_short_un;

typedef union
{
	u_long long_val;
	u_short short_val[2];
	u_char char_val[4];
} u_long_un;

u_char get_bits(const u_long bitmap,const u_char from_bit,const u_char bits_number);
char *hex2string(const u_long number,const u_char size);

#endif GLOBALS_H