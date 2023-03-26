/* This file is part of IntelliNote application developed by Stefan-Mihai MOGA.

IntelliNote is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliNote is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliNote. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// IntelliNoteDoc.cpp : implementation of the CIntelliNoteDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IntelliNote.h"
#endif

#include "IntelliNoteDoc.h"
#include "CntrItem.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIntelliNoteDoc

IMPLEMENT_DYNCREATE(CIntelliNoteDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CIntelliNoteDoc, CRichEditDoc)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_POPUP, &CIntelliNoteDoc::OnUpdateObjectVerbPopup)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

// CIntelliNoteDoc construction/destruction

CIntelliNoteDoc::CIntelliNoteDoc() noexcept
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

}

CIntelliNoteDoc::~CIntelliNoteDoc()
{
}

BOOL CIntelliNoteDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CIntelliNoteDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CIntelliNoteCntrItem(preo, const_cast<CIntelliNoteDoc*>(this));
}

// CIntelliNoteDoc serialization

void CIntelliNoteDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CIntelliNoteDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CIntelliNoteDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CIntelliNoteDoc::SetSearchContent(const CString& value)
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

// CIntelliNoteDoc diagnostics

#ifdef _DEBUG
void CIntelliNoteDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CIntelliNoteDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

// CIntelliNoteDoc commands
