/* Copyright (C) 2022-2026 Stefan-Mihai MOGA
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

// dllmain.h : Declaration of module class.

class CIntelliNoteHandlersModule : public ATL::CAtlDllModuleT<CIntelliNoteHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_IntelliNoteHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_INTELLINOTEHANDLERS, "{ffe9a438-9154-48bc-9e40-12c4c7db29b8}")
};

extern class CIntelliNoteHandlersModule _AtlModule;
