/* This file is part of IntelliNote application developed by Stefan-Mihai MOGA.

IntelliNote is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Open
Source Initiative, either version 3 of the License, or any later version.

IntelliNote is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
IntelliNote. If not, see <http://www.opensource.org/licenses/gpl-3.0.html>*/

// CntrItem.h : interface of the CIntelliNoteCntrItem class
//

#pragma once

class CIntelliNoteDoc;
class CIntelliNoteView;

class CIntelliNoteCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CIntelliNoteCntrItem)

// Constructors
public:
	CIntelliNoteCntrItem(REOBJECT* preo = nullptr, CIntelliNoteDoc* pContainer = nullptr);
		// Note: pContainer is allowed to be null to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-null document pointer

// Attributes
public:
	CIntelliNoteDoc* GetDocument()
		{ return reinterpret_cast<CIntelliNoteDoc*>(CRichEditCntrItem::GetDocument()); }
	CIntelliNoteView* GetActiveView()
		{ return reinterpret_cast<CIntelliNoteView*>(CRichEditCntrItem::GetActiveView()); }

// Implementation
public:
	~CIntelliNoteCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

