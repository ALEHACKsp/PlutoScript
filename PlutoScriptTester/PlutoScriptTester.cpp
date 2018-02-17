// PlutoScriptTester.cpp: Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
#include "PlutoScriptTester.h"
#include "HookManager.h"
#include "FunctionManager.h"

void OnSay(Entity* x,int y,char* z)
{
	std::string a(z);
	a = a + "\n";
	FunctionManager::WriteToServerConsole(a);
}

void PlutoScriptTester::Entry()
{
	FunctionManager::WriteToServerConsole("Loaded!\n");
	HookManager::InstallOnSay(OnSay);
}
