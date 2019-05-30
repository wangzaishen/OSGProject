
// MFC1View.h : CMFC1View ��Ľӿ�
//

#pragma once

#include "MFC_OSG.h"
class CMFC1View : public CView
{
protected: // �������л�����
	CMFC1View();
	DECLARE_DYNCREATE(CMFC1View)

// ����
public:
	CMFC1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CMFC1View();
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
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MFC1View.cpp �еĵ��԰汾
inline CMFC1Doc* CMFC1View::GetDocument() const
   { return reinterpret_cast<CMFC1Doc*>(m_pDocument); }
#endif

