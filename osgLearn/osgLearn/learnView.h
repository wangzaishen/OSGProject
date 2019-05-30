#pragma once
//#include "afxwin.h"
class learnView :
	public CWnd
{
public:
	learnView(void);
	~learnView(void);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpen();


};

