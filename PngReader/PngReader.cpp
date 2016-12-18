#include <conio.h>
#include <winsock2.h>
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdlib.h>
#include "Globals.h"
#include "Memlib.h"

#define IHDR_CHUNK_SIZE 17
#define PLTE_CHUNK_SIZE 3 
const char file_descr[9]="\x89\x50\x4E\x47\x0D\x0A\x1A\x0A";


typedef struct chunk
{
	u_long_un ch_length;
	u_long_un ch_type;
} chunk_t;

typedef struct IHDR_chunk
{
	u_long_un width;
	u_long_un height;
	u_char bit_depth;
	u_char color_type;
	u_char comp_method;
	u_char filter_method;
	u_char interlace_mehtod;
	u_long_un crc;
} IHDR_chunk_t;

typedef struct PLTE_chunk
{
	u_char red;
	u_char green;
	u_char blue;
} PLTE_chunk_t;

struct zlib_header
{
	struct sCMF
	{
		u_char CM;
		u_char CINFO;
	} CM;
	struct sFLG
	{
		u_char FCHECK;
		u_char FDICT;
		u_char FLEVEL;
	} FLG;
} zlib;
void main()
{
	u_char buffer[1024];
	chunk_t current_chunk;
	IHDR_chunk_t ihdr_chunk;
//	PLTE_chunk_t plte_chunk;
	PLTE_chunk_t *palette;
	u_long palette_size;

	ifstream png_file("im.png",ios::binary|ios::in);
	png_file.read(buffer,strlen(file_descr));
	buffer[8]='\x0';
	if (strcmp((char *)buffer,file_descr))
	{
		cerr<<"Bad file descriptor"<<endl;
		exit(0);
	}
	png_file.read((char *)&current_chunk,sizeof(chunk_t));
	cout<<"Current chunk length: "<<ntohl(current_chunk.ch_length.long_val)<<endl;
	cout<<"Current chunk type: "<<current_chunk.ch_type.char_val[0]
		<<current_chunk.ch_type.char_val[1]
		<<current_chunk.ch_type.char_val[2]
		<<current_chunk.ch_type.char_val[3]<<endl;
	if (current_chunk.ch_type.char_val[0]!='I'
		||current_chunk.ch_type.char_val[1]!='H'
		||current_chunk.ch_type.char_val[2]!='D'
		||current_chunk.ch_type.char_val[3]!='R')
	{
		cerr<<"Unexpected chunk type"<<endl;
		exit(0);
	}
	png_file.read((char *)&ihdr_chunk,IHDR_CHUNK_SIZE);
	cout<<"Width : "<<ntohl(ihdr_chunk.width.long_val)<<endl
		<<"Height : "<<ntohl(ihdr_chunk.height.long_val)<<endl
		<<"Bit Depth : "<<(int)ihdr_chunk.bit_depth<<endl
		<<"Color Type : "<<(int)ihdr_chunk.color_type<<endl
		<<"Compression method : "<<(int)ihdr_chunk.comp_method<<endl
		<<"Filter method : "<<(int)ihdr_chunk.filter_method<<endl
		<<"Interlace method : "<<(int)ihdr_chunk.interlace_mehtod<<endl;
	if (ihdr_chunk.comp_method||ihdr_chunk.filter_method)
	{
		cerr<<"Unexpected IHDR chunk values"<<endl;
		exit(0);
	}

	png_file.read((char *)&current_chunk,sizeof(chunk_t));
	cout<<"Current chunk length: "<<ntohl(current_chunk.ch_length.long_val)<<endl;
	cout<<"Current chunk type: "<<current_chunk.ch_type.char_val[0]
		<<current_chunk.ch_type.char_val[1]
		<<current_chunk.ch_type.char_val[2]
		<<current_chunk.ch_type.char_val[3]<<endl;
	if (current_chunk.ch_type.char_val[0]!='P'
		||current_chunk.ch_type.char_val[1]!='L'
		||current_chunk.ch_type.char_val[2]!='T'
		||current_chunk.ch_type.char_val[3]!='E')
	{
		cerr<<"Unexpected chunk type"<<endl;
		exit(0);
	}
	palette_size=ntohl(current_chunk.ch_length.long_val)/PLTE_CHUNK_SIZE;
	palette=(PLTE_chunk_t *)palloc(palette_size);
	for (int i=0; i<palette_size; i++)
	{
		png_file.read((char *)&palette[i],PLTE_CHUNK_SIZE);
		cout<<i<<" Color :"<<endl
			<<"\tRed:\t"<<(int)palette[i].red<<endl
			<<"\tGreen:\t"<<(int)palette[i].green<<endl
			<<"\tBlue:\t"<<(int)palette[i].blue<<endl;
	}
	/*passing PLTE chunk CRC*/
	png_file.seekg(4,ios::cur);
	
	png_file.read((char *)&current_chunk,sizeof(chunk_t));
	cout<<"Current chunk length: "<<ntohl(current_chunk.ch_length.long_val)<<endl;
	cout<<"Current chunk type: "<<current_chunk.ch_type.char_val[0]
		<<current_chunk.ch_type.char_val[1]
		<<current_chunk.ch_type.char_val[2]
		<<current_chunk.ch_type.char_val[3]<<endl;
	if (current_chunk.ch_type.char_val[0]!='I'
		||current_chunk.ch_type.char_val[1]!='D'
		||current_chunk.ch_type.char_val[2]!='A'
		||current_chunk.ch_type.char_val[3]!='T')
	{
		cerr<<"Unexpected chunk type"<<endl;
		exit(0);
	}
	png_file.read(buffer,2);
	zlib.CM.CM=get_bits(buffer[0],0,4);
	zlib.CM.CINFO=get_bits(buffer[0],4,4);
	zlib.FLG.FCHECK=get_bits(buffer[1],0,5);
	zlib.FLG.FDICT=get_bits(buffer[1],5,1);
	zlib.FLG.FLEVEL=get_bits(buffer[1],6,2);
	cout<<"CM : "<<(int)zlib.CM.CM<<endl
		<<"CINFO : "<<(int)zlib.CM.CINFO<<endl
		<<"FCHECK : "<<(int)zlib.FLG.FCHECK
		<<((buffer[0]*256+buffer[1])%31 ? " Incorrect" : " Correct")<<endl
		<<"FDICT : "<<(int)zlib.FLG.FDICT<<endl
		<<"FLEVEL : "<<(int)zlib.FLG.FLEVEL<<endl;

	png_file.close();
}