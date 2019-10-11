
// EASE0002View.cpp : implementation of the CEASE0002View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EASE0002.h"
#endif

#include "EASE0002Doc.h"
#include "EASE0002View.h"
#include "EASViewDlg.h"
#include "EaseData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEASE0002View

IMPLEMENT_DYNCREATE(CEASE0002View, CView)

BEGIN_MESSAGE_MAP(CEASE0002View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEASE0002View construction/destruction

CEASE0002View::CEASE0002View()
{
	// TODO: add construction code here

}

CEASE0002View::~CEASE0002View()
{
}

BOOL CEASE0002View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEASE0002View drawing

void CEASE0002View::OnDraw(CDC* /*pDC*/)
{
	CEASE0002Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CEASE0002View printing

BOOL CEASE0002View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEASE0002View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEASE0002View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEASE0002View diagnostics

#ifdef _DEBUG
void CEASE0002View::AssertValid() const
{
	CView::AssertValid();
}

void CEASE0002View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEASE0002Doc* CEASE0002View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEASE0002Doc)));
	return (CEASE0002Doc*)m_pDocument;
}
#endif //_DEBUG


// CEASE0002View message handlers


void CEASE0002View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

}
