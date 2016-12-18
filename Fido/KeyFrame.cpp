#include <GL/Glut.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
//#include <crtdbg.h>
//#include <new.h>
#include "Includes.h" 
#include "KeyFrame.h"

KeyFrame::KeyFrame(const unsigned char frames_num,treenode *iObject,float *iMatrix,const bool type):
frames_number(frames_num),keyframe_type(type)
{
	keys_number=0;
	frame_counter=0;
	root_object=iObject;
	root_matrix=iMatrix;
}

char KeyFrame::CheckKey(const unsigned char key) const
{
	bool flag=true;
	int i=0;
	while (i<keys_number&&flag)
	{
		if (keys_index[i]==key)
			flag=false;
		else
			i++;
	}
	if (flag)
		return -1;
	else
		return i;
}

void KeyFrame::AddKey(const unsigned char key)
{
	//unsigned char *temp;
	keys_number++;
	//temp=new unsigned char[keys_number];
	keys_index=(unsigned char *)realloc(keys_index,sizeof(unsigned char)*keys_number);
	//assert(temp!=NULL);
	//memcpy(temp,keys_index,sizeof(unsigned char)*(keys_number-1));
	//delete []keys_index;
	//keys_index=temp;
	//delete []temp;
	keys_index[keys_number-1]=key;
}

void KeyFrame::AddFrame(void)
{
	//frame *temp;
	//temp=new frame[keys_number];
	//assert(temp!=NULL);
	//memcpy(temp,frame_buffer,sizeof(frame)*(keys_number-1));
	//delete []frame_buffer;
	//frame_buffer=temp;
	//delete []temp;
	frame_buffer=(frame *)realloc(frame_buffer,sizeof(frame)*keys_number);
	frame_buffer[keys_number-1].objects_number=0;
}

void KeyFrame::AddObject(const unsigned char key,treenode *node)
{
	//treenode **temp;
	frame_buffer[key].objects_number++;
	//temp=new treenode *[frame_buffer[key].objects_number];
	//assert(temp!=NULL);
	//memcpy(temp,frame_buffer[key].objects_array,
	//	sizeof(treenode *)*(frame_buffer[key].objects_number-1));
	//delete []frame_buffer[key].objects_array;
	//frame_buffer[key].objects_array=temp;
	//delete []temp;
	//_set_new_mode(1);
	
	frame_buffer[key].objects_array=
		(treenode **)realloc(frame_buffer[key].objects_array,
		sizeof(treenode *)*frame_buffer[key].objects_number);
	frame_buffer[key].objects_array[frame_buffer[key].objects_number-1]=node;
}

void KeyFrame::SetTranslateAnim(const unsigned char key,const float *position)
{
	//float *temp;
	//temp=new float [frame_buffer[key].objects_number*3];
	//assert(temp!=NULL);
	//memcpy(temp,frame_buffer[key].translation_array,
	//	sizeof(float)*(frame_buffer[key].objects_number-1)*3);
	//delete frame_buffer[key].translation_array;
	//frame_buffer[key].translation_array=temp;
	//delete []temp;
	frame_buffer[key].translation_array=(float *)realloc(frame_buffer[key].translation_array,
		sizeof(float)*frame_buffer[key].objects_number*3);

	memcpy(frame_buffer[key].translation_array+3*(frame_buffer[key].objects_number-1),
		position,sizeof(float)*3);
}

void KeyFrame::SetRotationAnim(const unsigned char key,const float *position)
{
	//float *temp;
	//temp=new float [frame_buffer[key].objects_number*3];
	//assert(temp!=NULL);
	//memcpy(temp,frame_buffer[key].rotation_array,
	//	sizeof(float)*(frame_buffer[key].objects_number-1)*3);
	//delete frame_buffer[key].rotation_array;
	//frame_buffer[key].rotation_array=temp;
	//delete []temp;
	frame_buffer[key].rotation_array=(float *)realloc(frame_buffer[key].rotation_array,
		sizeof(float)*frame_buffer[key].objects_number*3);

	memcpy(frame_buffer[key].rotation_array+3*(frame_buffer[key].objects_number-1),
		position,sizeof(float)*3);
}

void KeyFrame::Attach2Frame(const unsigned char frame,
							treenode *node,
							const float tx,const float ty,const float tz,
							const float rx,const float ry,const float rz)
{
	char index=KeyFrame::CheckKey(frame);
	float tvector[3]={tx,ty,tz};
	float rvector[3]={rx,ry,rz};
	if (index==-1)
	{
		KeyFrame::AddKey(frame);
		KeyFrame::AddFrame();
		index=keys_number-1;
		frame_buffer[index].objects_array=new treenode *;
		frame_buffer[index].translation_array=new float;
		frame_buffer[index].rotation_array=new float;
	}

	KeyFrame::AddObject(index,node);
	KeyFrame::SetTranslateAnim(index,tvector);
	KeyFrame::SetRotationAnim(index,rvector);
}

void KeyFrame::Play(void)
{
	static int key_counter=0;
	static int dframes;
	float dtx,dty,dtz;
	float drx,dry,drz;

	if (keys_index[key_counter]==frame_counter&&frame_counter!=(frames_number-1)
		&&key_counter!=keys_number-1)
	{
		key_counter++;
		dframes=(keys_index[key_counter]-keys_index[key_counter-1]);
	}
	if (frame_counter!=frames_number)
	{
		for (int i=0; i<frame_buffer[key_counter].objects_number; i++)
		{
			dtx=(frame_buffer[key_counter].translation_array[i*3]-
				frame_buffer[key_counter-1].translation_array[i*3])/
				dframes;

			dty=(frame_buffer[key_counter].translation_array[i*3+1]-
				frame_buffer[key_counter-1].translation_array[i*3+1])/
				dframes;

			dtz=(frame_buffer[key_counter].translation_array[i*3+2]-
				frame_buffer[key_counter-1].translation_array[i*3+2])/
				dframes;

			drx=(frame_buffer[key_counter].rotation_array[i*3]-
				frame_buffer[key_counter-1].rotation_array[i*3])/
				dframes;

			dry=(frame_buffer[key_counter].rotation_array[i*3+1]-
				frame_buffer[key_counter-1].rotation_array[i*3+1])/
				dframes;

			drz=(frame_buffer[key_counter].rotation_array[i*3+2]-
				frame_buffer[key_counter-1].rotation_array[i*3+2])/
				dframes;
			glLoadIdentity();
			if (frame_buffer[key_counter].objects_array[i]==root_object)
				glMultMatrixf(root_matrix);
			glTranslatef(frame_buffer[key_counter].objects_array[i]->center[0],
				frame_buffer[key_counter].objects_array[i]->center[1],
				frame_buffer[key_counter].objects_array[i]->center[2]);
				//if (drx!=0.0)
					glRotatef(frame_buffer[key_counter-1].rotation_array[i*3]+
						drx*(frame_counter+1),1.0,0.0,0.0);
				//if (dry!=0.0)
					glRotatef(frame_buffer[key_counter-1].rotation_array[i*3+1]+
						dry*(frame_counter+1),0.0,1.0,0.0);
				//if (drz!=0.0)
					glRotatef(frame_buffer[key_counter-1].rotation_array[i*3+2]+
						drz*(frame_counter+1),0.0,0.0,1.0);
				glTranslatef(frame_buffer[key_counter-1].translation_array[i*3]+
						dtx*(frame_counter+1),
					frame_buffer[key_counter-1].translation_array[i*3+1]+
						dty*(frame_counter+1),
					frame_buffer[key_counter-1].translation_array[i*3+2]+
						dtz*(frame_counter+1));
				
			glTranslatef(-frame_buffer[key_counter].objects_array[i]->center[0],
				-frame_buffer[key_counter].objects_array[i]->center[1],
				-frame_buffer[key_counter].objects_array[i]->center[2]);
			glGetFloatv(GL_MODELVIEW_MATRIX, 
					frame_buffer[key_counter].objects_array[i]->matrix);
			
		}
	}

	if (frame_counter!=keys_index[keys_number-1])
		frame_counter++;
	else
		if (keyframe_type)
		{
			frame_counter=0;
			key_counter=0;
		}
}

KeyFrame::~KeyFrame()
{
	delete []frame_buffer;
	delete []keys_index;
}