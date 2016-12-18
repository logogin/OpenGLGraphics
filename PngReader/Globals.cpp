#include "Includes.h"
#include "Globals.h"

u_char get_bits(const u_long bitmap,const u_char from_bit,const u_char bits_number)
{
	u_long temp=bitmap;
	u_char result=0;
	//for (int i=0; i<from_bit; i++)
	temp>>=from_bit;
	result=(u_char)temp&~(0xFFFFFFFF<<bits_number);
	return result;
}

char *hex2string(const u_long number,const u_char size)
{
	const char table[]="0123456789ABCDEF";
	char *result;
	u_long temp=number;
	u_char digit;
	result=new char[size+1];
	for (int i=0; i<size; i++)
	{
		digit=(u_char)temp&0x0000000F;
		temp>>=4;
		result[size-i-1]=table[digit];
	}
	result[size]='\x0';
	return strdup(result);
}