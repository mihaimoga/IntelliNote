// dllmain.h : Declaration of module class.

class CIntelliNoteHandlersModule : public ATL::CAtlDllModuleT<CIntelliNoteHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_IntelliNoteHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_INTELLINOTEHANDLERS, "{ffe9a438-9154-48bc-9e40-12c4c7db29b8}")
};

extern class CIntelliNoteHandlersModule _AtlModule;
