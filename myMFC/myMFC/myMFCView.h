
// myMFCView.h : CmyMFCView ��Ľӿ�
//

#pragma once
//#include "osgFrame.h"
#include "MFC_OSG.h"

class CmyMFCView : public CView
{
protected: // �������л�����
	CmyMFCView();
	DECLARE_DYNCREATE(CmyMFCView)

// ����
public:
	CmyMFCDoc* GetDocument() const;

// ����
public:

	//osgFrame* mOSG;
	cOSG* mOSG;
	HANDLE mThreadHandle;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	int OnCreate(LPCREATESTRUCT lpcs);
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnInitialUpdate();
	void OnDestroy();
protected:

// ʵ��
public:
	virtual ~CmyMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // myMFCView.cpp �еĵ��԰汾
inline CmyMFCDoc* CmyMFCView::GetDocument() const
   { return reinterpret_cast<CmyMFCDoc*>(m_pDocument); }
#endif

