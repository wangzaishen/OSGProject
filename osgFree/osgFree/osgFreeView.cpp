
// osgFreeView.cpp : CosgFreeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "osgFree.h"
#endif

#include "osgFreeDoc.h"
#include "osgFreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CosgFreeView

IMPLEMENT_DYNCREATE(CosgFreeView, CView)

BEGIN_MESSAGE_MAP(CosgFreeView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CosgFreeView 构造/析构

CosgFreeView::CosgFreeView()
{
	// TODO: 在此处添加构造代码

}

CosgFreeView::~CosgFreeView()
{
}

BOOL CosgFreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CosgFreeView 绘制

void CosgFreeView::OnDraw(CDC* /*pDC*/)
{
	CosgFreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CosgFreeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CosgFreeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CosgFreeView 诊断

#ifdef _DEBUG
void CosgFreeView::AssertValid() const
{
	CView::AssertValid();
}

void CosgFreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CosgFreeDoc* CosgFreeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CosgFreeDoc)));
	return (CosgFreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CosgFreeView 消息处理程序
