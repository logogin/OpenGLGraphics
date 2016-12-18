
#ifndef KeyFrame_H
#define KeyFrame_H
#include "Includes.h"

class KeyFrame
{
	public:
		KeyFrame(const unsigned char,treenode *,float *,const bool);
		~KeyFrame();
		void Attach2Frame(const unsigned char,treenode *, const float,const float,const float,
			const float,const float,const float);
		void Play();
	private:

		void AddObject(const unsigned char, treenode *);
		void SetTranslateAnim(const unsigned char,const float *);
		void SetRotationAnim(const unsigned char, const float *);
		char CheckKey(const unsigned char) const;
		void AddKey(const unsigned char);
		void AddFrame(void);
		
		unsigned char frame_counter;
		unsigned char keys_number;
		unsigned char frames_number;
		unsigned char *keys_index;
		treenode *root_object;
		float *root_matrix;
		bool keyframe_type;
		
		struct frame
		{
			unsigned char objects_number;
			treenode **objects_array;
			float *translation_array;
			float *rotation_array;
		} *frame_buffer;
};

#endif KeyFrame_H