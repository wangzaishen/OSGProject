
// osgFreeView.h : CosgFreeView ��Ľӿ�
//

#pragma once


class CosgFreeView : public CView
{
protected: // �������л�����
	CosgFreeView();
	DECLARE_DYNCREATE(CosgFreeView)

// ����
public:
	CosgFreeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CosgFreeView();
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

#ifndef _DEBUG  // osgFreeView.cpp �еĵ��԰汾
inline CosgFreeDoc* CosgFreeView::GetDocument() const
   { return reinterpret_cast<CosgFreeDoc*>(m_pDocument); }
#endif

