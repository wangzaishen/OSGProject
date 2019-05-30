
// osgLearnView.cpp : CosgLearnView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "osgLearn.h"
#endif

#include "osgLearnDoc.h"
#include "osgLearnView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CosgLearnView

IMPLEMENT_DYNCREATE(CosgLearnView, CView)

BEGIN_MESSAGE_MAP(CosgLearnView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CosgLearnView 构造/析构

CosgLearnView::CosgLearnView()
{
	// TODO: 在此处添加构造代码

}

CosgLearnView::~CosgLearnView()
{
}

BOOL CosgLearnView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CosgLearnView 绘制

void CosgLearnView::OnDraw(CDC* /*pDC*/)
{
	CosgLearnDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CosgLearnView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CosgLearnView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CosgLearnView 诊断

#ifdef _DEBUG
void CosgLearnView::AssertValid() const
{
	CView::AssertValid();
}

void CosgLearnView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CosgLearnDoc* CosgLearnView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CosgLearnDoc)));
	return (CosgLearnDoc*)m_pDocument;
}
#endif //_DEBUG


// CosgLearnView 消息处理程序
