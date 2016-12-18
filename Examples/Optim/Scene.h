// Scene.h: interface for the CScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__624BA070_A15B_11D4_8EC2_000000000000__INCLUDED_)
#define AFX_SCENE_H__624BA070_A15B_11D4_8EC2_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CScene  
{
public:
	double MyX;
	double MyY;
	double MyZ;
	double MyV;
	double MyH;
	double Speed;

public:
	void ResizeViewport( int w, int h);
	void ShutDown();
	void HandleControls();
	void Show();
	void SetMyView();
	void Init();
	CScene();
	virtual ~CScene();

};

#endif // !defined(AFX_SCENE_H__624BA070_A15B_11D4_8EC2_000000000000__INCLUDED_)
