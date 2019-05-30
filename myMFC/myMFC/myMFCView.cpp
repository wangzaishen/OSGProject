
// myMFCView.cpp : CmyMFCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CmyMFCView ����/����

CmyMFCView::CmyMFCView()
{
	// TODO: �ڴ˴���ӹ������

}

CmyMFCView::~CmyMFCView()
{
}

BOOL CmyMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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
// CmyMFCView ����

void CmyMFCView::OnDraw(CDC* /*pDC*/)
{
	CmyMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CmyMFCView ���

#ifdef _DEBUG
void CmyMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CmyMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmyMFCDoc* CmyMFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmyMFCDoc)));
	return (CmyMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CmyMFCView ��Ϣ�������
