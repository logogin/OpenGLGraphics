
#ifndef Includes_H
#define Includes_H

typedef struct treenode
{	
	float matrix[16];
	float center[3];
	void (*fptr)();
	unsigned char children_number;
	struct treenode **children;
} treenode;

#endif Includes_H