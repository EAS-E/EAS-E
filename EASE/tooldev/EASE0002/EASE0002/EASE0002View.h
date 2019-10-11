
// EASE0002View.h : interface of the CEASE0002View class
//

#pragma once


class CEASE0002View : public CView
{
protected: // create from serialization only
	CEASE0002View();
	DECLARE_DYNCREATE(CEASE0002View)

// Attributes
public:
	CEASE0002Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEASE0002View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in EASE0002View.cpp
inline CEASE0002Doc* CEASE0002View::GetDocument() const
   { return reinterpret_cast<CEASE0002Doc*>(m_pDocument); }
#endif

