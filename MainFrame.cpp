/* This file is part of IntelliNote application developed by Mihai MOGA.

IntelliNote is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliNote is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliNote.  If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// MainFrame.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "IntelliNote.h"
#include "IntelliNoteDoc.h"
#include "IntelliNoteView.h"

#include "MainFrame.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_COMMAND(ID_DATE_TIME, &CMainFrame::OnDateTime)
	ON_COMMAND(ID_UNDO, &CMainFrame::OnUndo)
	ON_UPDATE_COMMAND_UI(ID_UNDO, &CMainFrame::OnUpdateUndo)
	ON_COMMAND(ID_REDO, &CMainFrame::OnRedo)
	ON_UPDATE_COMMAND_UI(ID_REDO, &CMainFrame::OnUpdateRedo)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // other styles available...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
	mdiTabParams.m_bTabIcons = FALSE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = TRUE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Create a caption bar:
	if (!CreateCaptionBar())
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// Switch the order of document name and application name on the window title bar. This
	// improves the usability of the taskbar because the document name is visible with the thumbnail.
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CMDIFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != nullptr);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}

void CMainFrame::OnDateTime()
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// Get the active view attached to the active MDI child window.
	CIntelliNoteView *pView = (CIntelliNoteView*)pChild->GetActiveView();

	// Get the active document attached to the active MDI child window.
	// CIntelliNoteDoc *pDoc = (CIntelliNoteDoc*)pView->GetDocument();

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
	/*time_t ltime;
	wchar_t buffer[0x100];
	time(&ltime);
	errno_t err = _wctime_s(buffer, 0x100, &ltime);
	ASSERT(err == 0);*/
	CRichEditCtrl& pCtrl = pView->GetRichEditCtrl();
	pCtrl.ReplaceSel(CString(lpszBuffer));
}

void CMainFrame::OnUndo()
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// Get the active view attached to the active MDI child window.
	CIntelliNoteView *pView = (CIntelliNoteView*)pChild->GetActiveView();

	// Get the active document attached to the active MDI child window.
	// CIntelliNoteDoc *pDoc = (CIntelliNoteDoc*)pView->GetDocument();

	CRichEditCtrl& pCtrl = pView->GetRichEditCtrl();
	pCtrl.Undo();
}

void CMainFrame::OnUpdateUndo(CCmdUI *pCmdUI)
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// Get the active view attached to the active MDI child window.
	CIntelliNoteView *pView = (CIntelliNoteView*)pChild->GetActiveView();

	// Get the active document attached to the active MDI child window.
	// CIntelliNoteDoc *pDoc = (CIntelliNoteDoc*)pView->GetDocument();

	CRichEditCtrl& pCtrl = pView->GetRichEditCtrl();
	pCmdUI->Enable(pCtrl.CanUndo());
}

void CMainFrame::OnRedo()
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// Get the active view attached to the active MDI child window.
	CIntelliNoteView *pView = (CIntelliNoteView*)pChild->GetActiveView();

	// Get the active document attached to the active MDI child window.
	// CIntelliNoteDoc *pDoc = (CIntelliNoteDoc*)pView->GetDocument();

	CRichEditCtrl& pCtrl = pView->GetRichEditCtrl();
	pCtrl.Redo();
}

void CMainFrame::OnUpdateRedo(CCmdUI *pCmdUI)
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();

	// Get the active view attached to the active MDI child window.
	CIntelliNoteView *pView = (CIntelliNoteView*)pChild->GetActiveView();

	// Get the active document attached to the active MDI child window.
	// CIntelliNoteDoc *pDoc = (CIntelliNoteDoc*)pView->GetDocument();

	CRichEditCtrl& pCtrl = pView->GetRichEditCtrl();
	pCmdUI->Enable(pCtrl.CanRedo());
}
