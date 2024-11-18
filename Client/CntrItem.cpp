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

// CntrItem.cpp : implementation of the CIntelliNoteCntrItem class
//

#include "pch.h"
#include "framework.h"
#include "IntelliNote.h"

#include "IntelliNoteDoc.h"
#include "IntelliNoteView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIntelliNoteCntrItem implementation

IMPLEMENT_SERIAL(CIntelliNoteCntrItem, CRichEditCntrItem, 0)

CIntelliNoteCntrItem::CIntelliNoteCntrItem(REOBJECT* preo, CIntelliNoteDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
}

CIntelliNoteCntrItem::~CIntelliNoteCntrItem()
{
	// TODO: add cleanup code here
}

// CIntelliNoteCntrItem diagnostics

#ifdef _DEBUG
void CIntelliNoteCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CIntelliNoteCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif
