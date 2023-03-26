// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "IntelliNoteHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CIntelliNoteHandlersModule _AtlModule;

class CIntelliNoteHandlersApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CIntelliNoteHandlersApp, CWinApp)
END_MESSAGE_MAP()

CIntelliNoteHandlersApp theApp;

BOOL CIntelliNoteHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, nullptr))
		return FALSE;
	return CWinApp::InitInstance();
}

int CIntelliNoteHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
