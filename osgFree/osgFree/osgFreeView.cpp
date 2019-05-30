
// osgFreeView.cpp : CosgFreeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CosgFreeView ����/����

CosgFreeView::CosgFreeView()
{
	// TODO: �ڴ˴���ӹ������

}

CosgFreeView::~CosgFreeView()
{
}

BOOL CosgFreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CosgFreeView ����

void CosgFreeView::OnDraw(CDC* /*pDC*/)
{
	CosgFreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CosgFreeView ���

#ifdef _DEBUG
void CosgFreeView::AssertValid() const
{
	CView::AssertValid();
}

void CosgFreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CosgFreeDoc* CosgFreeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CosgFreeDoc)));
	return (CosgFreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CosgFreeView ��Ϣ�������
