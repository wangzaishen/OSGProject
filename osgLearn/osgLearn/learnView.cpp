#include "StdAfx.h"
#include "learnView.h"
#include "osgLearn.h"

BEGIN_MESSAGE_MAP(learnView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
END_MESSAGE_MAP()

learnView::learnView(void)
{
}


learnView::~learnView(void)
{
}

BOOL learnView::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CWnd::PreCreateWindow(cs))
	{
		return FALSE;
	}

	return TRUE;
}

void learnView::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	CBrush brush(RGB(0,0,100));
	::GetClientRect(m_hWnd, &rect);
	dc.FillRect(&rect, &brush);
}

void learnView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

}


void learnView::OnFileOpen()
{
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal() == IDOK)
	{

	}
}
