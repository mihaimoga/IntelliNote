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

// IntelliNote.h : main header file for the IntelliNote application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "sinstance.h"

// CIntelliNoteApp:
// See IntelliNote.cpp for the implementation of this class
//

class CIntelliNoteApp : public CWinAppEx
{
public:
	CIntelliNoteApp() noexcept;

public:
	CInstanceChecker m_pInstanceChecker;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIntelliNoteApp theApp;
