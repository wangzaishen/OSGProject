
// MFC1View.cpp : CMFC1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC1.h"
#endif

#include "MFC1Doc.h"
#include "MFC1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
cOSG* mOSG;
HANDLE mThreadHandle;

// CMFC1View

IMPLEMENT_DYNCREATE(CMFC1View, CView)

BEGIN_MESSAGE_MAP(CMFC1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFC1View 构造/析构

CMFC1View::CMFC1View()
{
	// TODO: 在此处添加构造代码

}

CMFC1View::~CMFC1View()
{
}

BOOL CMFC1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC1View 绘制

void CMFC1View::OnDraw(CDC* /*pDC*/)
{
	CMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CMFC1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC1View 诊断

#ifdef _DEBUG
void CMFC1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC1Doc* CMFC1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC1Doc)));
	return (CMFC1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC1View 消息处理程序


void CMFC1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	mOSG->InitOSG("cow.osg");
	mThreadHandle = (HANDLE)_beginthread(&cOSG::Render, 0, mOSG);
}


void CMFC1View::OnDestroy()
{
	CView::OnDestroy();
	//CView::OnDestroy();
	if(mOSG != 0)
	{
		delete mOSG;
	}
	WaitForSingleObject(mThreadHandle, 1000);
	// TODO: 在此处添加消息处理程序代码
}


int CMFC1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	else
	{
		mOSG = new cOSG(m_hWnd);
	}
	// TODO:  在此添加您专用的创建代码

	return 0;
}


BOOL CMFC1View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(0 == mOSG)
	{
		return CView::OnEraseBkgnd(pDC);
	}
	else
	{
		return FALSE;
	}

	//return CWnd::OnEraseBkgnd(pDC);
	//return CView::OnEraseBkgnd(pDC);
	return CView::OnEraseBkgnd(pDC);
}
