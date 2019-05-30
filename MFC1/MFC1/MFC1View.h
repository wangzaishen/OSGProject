
// MFC1View.h : CMFC1View 类的接口
//

#pragma once

#include "MFC_OSG.h"
class CMFC1View : public CView
{
protected: // 仅从序列化创建
	CMFC1View();
	DECLARE_DYNCREATE(CMFC1View)

// 特性
public:
	CMFC1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFC1View();
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
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MFC1View.cpp 中的调试版本
inline CMFC1Doc* CMFC1View::GetDocument() const
   { return reinterpret_cast<CMFC1Doc*>(m_pDocument); }
#endif

