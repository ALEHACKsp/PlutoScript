// PlutoScriptTester.cpp: Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
#include "PlutoScriptTester.h"
#include "HookManager.h"
#include "FunctionManager.h"

void OnSay(Entity* x,int y,std::string z)
{	
	FunctionManager::WriteToServerConsole(z + "\n");
}

void OnConnect(Entity* e)
{
	FunctionManager::WriteToServerConsole(std::string(e->Shared.Client->Session.Clientstate.Name) + " connected \n");
}

void OnDisconnect(Entity* e)
{
	FunctionManager::WriteToServerConsole(std::string(e->Shared.Client->Session.Clientstate.Name) + " disconnected \n");
}

void PlutoScriptTester::Entry()
{
	//FunctionManager::WriteToServerConsole("Loaded!\n");
	HookManager::InstallOnSay(OnSay);
	HookManager::InstallOnConnect(OnConnect);
	HookManager::InstallOnDisconnect(OnDisconnect);
}
