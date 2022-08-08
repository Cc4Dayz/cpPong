
// cpPongDoc.cpp : implementation of the CcpPongDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "cpPong.h"
#endif

#include "cpPongDoc.h"
#include "cpPongView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CcpPongDoc

IMPLEMENT_DYNCREATE(CcpPongDoc, CDocument)

BEGIN_MESSAGE_MAP(CcpPongDoc, CDocument)
END_MESSAGE_MAP()


// CcpPongDoc construction/destruction

CcpPongDoc::CcpPongDoc() noexcept
{
	// TODO: add one-time construction code here

}

CcpPongDoc::~CcpPongDoc()
{
}

BOOL CcpPongDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CcpPongDoc serialization

void CcpPongDoc::Serialize(CArchive& ar)
{
	CFrameWndEx* pMain = (CFrameWndEx*)AfxGetMainWnd();
	CcpPongView* pView = (CcpPongView*)pMain->GetActiveView();

	if (ar.IsStoring())
	{

	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CcpPongDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CcpPongDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CcpPongDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CcpPongDoc diagnostics

#ifdef _DEBUG
void CcpPongDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CcpPongDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CcpPongDoc commands
