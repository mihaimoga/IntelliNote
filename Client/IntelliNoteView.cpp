/* Copyright (C) 2022-2025 Stefan-Mihai MOGA
This file is part of IntelliNote application developed by Stefan-Mihai MOGA.
IntelliNote is an alternative Windows version to the famous Microsoft OneNote!

IntelliNote is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliNote is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliNote. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// IntelliNoteView.cpp : implementation of the CIntelliNoteView class
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
#include "resource.h"
#include "IntelliNoteView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIntelliNoteView

IMPLEMENT_DYNCREATE(CIntelliNoteView, CRichEditView)

BEGIN_MESSAGE_MAP(CIntelliNoteView, CRichEditView)
	ON_WM_DESTROY()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIntelliNoteView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DATE_TIME, &CIntelliNoteView::OnDateTime)
	ON_COMMAND(ID_UNDO, &CIntelliNoteView::OnUndo)
	ON_UPDATE_COMMAND_UI(ID_UNDO, &CIntelliNoteView::OnUpdateUndo)
	ON_COMMAND(ID_REDO, &CIntelliNoteView::OnRedo)
	ON_UPDATE_COMMAND_UI(ID_REDO, &CIntelliNoteView::OnUpdateRedo)
END_MESSAGE_MAP()

// CIntelliNoteView construction/destruction

CIntelliNoteView::CIntelliNoteView() noexcept
{
	// TODO: add construction code here

}

CIntelliNoteView::~CIntelliNoteView()
{
}

BOOL CIntelliNoteView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CIntelliNoteView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch)
	SetMargins(CRect(720, 720, 720, 720));
}

// CIntelliNoteView printing

void CIntelliNoteView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIntelliNoteView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIntelliNoteView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != nullptr && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
   }
   CRichEditView::OnDestroy();
}

void CIntelliNoteView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIntelliNoteView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	UNREFERENCED_PARAMETER(point);
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CIntelliNoteView diagnostics

#ifdef _DEBUG
void CIntelliNoteView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CIntelliNoteView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CIntelliNoteDoc* CIntelliNoteView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIntelliNoteDoc)));
	return (CIntelliNoteDoc*)m_pDocument;
}
#endif //_DEBUG

// CIntelliNoteView message handlers

void CIntelliNoteView::OnDateTime()
{
	SYSTEMTIME sysTime;
	TCHAR lpszBuffer[0x100] = { 0, };
	TCHAR lpszDayOfWeek[0x100] = { 0, };
	TCHAR lpszMonth[0x100] = { 0, };
	GetLocalTime(&sysTime);

	switch (sysTime.wDayOfWeek)
	{
		case 0:
			_tcscpy_s(lpszDayOfWeek, _countof(lpszDayOfWeek), _T("Sunday"));
			break;
		case 1:
			_tcscpy_s(lpszDayOfWeek, _countof(lpszDayOfWeek), _T("Monday"));
			break;
		case 2:
			_tcscpy_s(lpszDayOfWeek, _countof(lpszDayOfWeek), _T("Tuesday"));
			break;
		case 3:
			_tcscpy_s(lpszDayOfWeek, _countof(lpszDayOfWeek), _T("Wednesday"));
			break;
		case 4:
			_tcscpy_s(lpszDayOfWeek, _countof(lpszDayOfWeek), _T("Thursday"));
			break;
		case 5:
			_tcscpy_s(lpszDayOfWeek, _countof(lpszDayOfWeek), _T("Friday"));
			break;
		case 6:
			_tcscpy_s(lpszDayOfWeek, _countof(lpszDayOfWeek), _T("Saturday"));
			break;
	}

	switch (sysTime.wMonth)
	{
		case 1:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("January"));
			break;
		case 2:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("February"));
			break;
		case 3:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("March"));
			break;
		case 4:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("April"));
			break;
		case 5:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("May"));
			break;
		case 6:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("June"));
			break;
		case 7:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("July"));
			break;
		case 8:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("August"));
			break;
		case 9:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("September"));
			break;
		case 10:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("October"));
			break;
		case 11:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("November"));
			break;
		case 12:
			_tcscpy_s(lpszMonth, _countof(lpszMonth), _T("December"));
			break;
	}

	_stprintf_s(lpszBuffer, _countof(lpszBuffer), _T("%s, %s %d, %d %02d:%02d:%02d"), lpszDayOfWeek, lpszMonth, sysTime.wDay, sysTime.wYear, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	CRichEditCtrl& pCtrl = GetRichEditCtrl();
	pCtrl.ReplaceSel(CString(lpszBuffer));
}

void CIntelliNoteView::OnUndo()
{
	CRichEditCtrl& pCtrl = GetRichEditCtrl();
	pCtrl.Undo();
}

void CIntelliNoteView::OnUpdateUndo(CCmdUI *pCmdUI)
{
	CRichEditCtrl& pCtrl = GetRichEditCtrl();
	pCmdUI->Enable(pCtrl.CanUndo());
}

void CIntelliNoteView::OnRedo()
{
	CRichEditCtrl& pCtrl = GetRichEditCtrl();
	pCtrl.Redo();
}

void CIntelliNoteView::OnUpdateRedo(CCmdUI *pCmdUI)
{
	CRichEditCtrl& pCtrl = GetRichEditCtrl();
	pCmdUI->Enable(pCtrl.CanRedo());
}
