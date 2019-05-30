
// myMFCView.cpp : CmyMFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "myMFC.h"
#endif

#include "myMFCDoc.h"
#include "myMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CmyMFCView

IMPLEMENT_DYNCREATE(CmyMFCView, CView)

BEGIN_MESSAGE_MAP(CmyMFCView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CmyMFCView 构造/析构

CmyMFCView::CmyMFCView()
{
	// TODO: 在此处添加构造代码

}

CmyMFCView::~CmyMFCView()
{
}

BOOL CmyMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}
int CmyMFCView::OnCreate(LPCREATESTRUCT lpcs)
{
	if(CView::OnCreate(lpcs) == -1)
	{
		return -1;
	}
	else
	{
		mOSG = new cOSG(m_hWnd);
	}
	//mOSG = new cOSG(m_hWnd);
	return 0;

}

BOOL CmyMFCView::OnEraseBkgnd(CDC* pDC)
{
	if(0 == mOSG)
	{
		return CView::OnEraseBkgnd(pDC);
	}
	else
	{
		return FALSE;
	}

	return CView::OnEraseBkgnd(pDC);

}

void CmyMFCView::OnDestroy()
{
	CView::OnDestroy();
	if(0 != mOSG)
	{
		delete mOSG;
	}

	WaitForSingleObject(mThreadHandle, 1000);


}
void CmyMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	std::string str = "free.osg";
	mOSG->InitOSG(str);
	mThreadHandle = (HANDLE)_beginthread(&cOSG::Render, 0, mOSG);
}
// CmyMFCView 绘制

void CmyMFCView::OnDraw(CDC* /*pDC*/)
{
	CmyMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CmyMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmyMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CmyMFCView 诊断

#ifdef _DEBUG
void CmyMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CmyMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmyMFCDoc* CmyMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmyMFCDoc)));
	return (CmyMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CmyMFCView 消息处理程序
