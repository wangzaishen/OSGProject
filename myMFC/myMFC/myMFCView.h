
// myMFCView.h : CmyMFCView 类的接口
//

#pragma once
//#include "osgFrame.h"
#include "MFC_OSG.h"

class CmyMFCView : public CView
{
protected: // 仅从序列化创建
	CmyMFCView();
	DECLARE_DYNCREATE(CmyMFCView)

// 特性
public:
	CmyMFCDoc* GetDocument() const;

// 操作
public:

	//osgFrame* mOSG;
	cOSG* mOSG;
	HANDLE mThreadHandle;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	int OnCreate(LPCREATESTRUCT lpcs);
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnInitialUpdate();
	void OnDestroy();
protected:

// 实现
public:
	virtual ~CmyMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // myMFCView.cpp 中的调试版本
inline CmyMFCDoc* CmyMFCView::GetDocument() const
   { return reinterpret_cast<CmyMFCDoc*>(m_pDocument); }
#endif

