
// MainFrmView.cpp : CMainFrmView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MainFrm.h"
#endif

#include "MainFrmDoc.h"
#include "MainFrmView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrmView

IMPLEMENT_DYNCREATE(CMainFrmView, CView)

BEGIN_MESSAGE_MAP(CMainFrmView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrmView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMainFrmView ����/����

CMainFrmView::CMainFrmView()
{
	// TODO: �ڴ˴���ӹ������

}

CMainFrmView::~CMainFrmView()
{
}

BOOL CMainFrmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMainFrmView ����

void CMainFrmView::OnDraw(CDC* /*pDC*/)
{
	CMainFrmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMainFrmView ��ӡ


void CMainFrmView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMainFrmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMainFrmView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMainFrmView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMainFrmView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMainFrmView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMainFrmView ���

#ifdef _DEBUG
void CMainFrmView::AssertValid() const
{
	CView::AssertValid();
}

void CMainFrmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainFrmDoc* CMainFrmView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainFrmDoc)));
	return (CMainFrmDoc*)m_pDocument;
}
#endif //_DEBUG


// CMainFrmView ��Ϣ�������
