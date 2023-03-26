/* This file is part of IntelliNote application developed by Stefan-Mihai MOGA.

IntelliNote is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliNote is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliNote. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// IntelliNoteView.h : interface of the CIntelliNoteView class
//

#pragma once

class CIntelliNoteCntrItem;

class CIntelliNoteView : public CRichEditView
{
protected: // create from serialization only
	CIntelliNoteView() noexcept;
	DECLARE_DYNCREATE(CIntelliNoteView)

// Attributes
public:
	CIntelliNoteDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CIntelliNoteView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IntelliNoteView.cpp
inline CIntelliNoteDoc* CIntelliNoteView::GetDocument() const
   { return reinterpret_cast<CIntelliNoteDoc*>(m_pDocument); }
#endif

