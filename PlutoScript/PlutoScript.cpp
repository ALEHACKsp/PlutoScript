// PlutoScript.cpp: Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
namespace PlutoScript
{
	using SpawnServerPrototype = void(__cdecl*)(int a1, int a2, int a3);
	SpawnServerPrototype SpawnServer;

	void HookedSpawnServer(int a1,int a2,int a3)
	{
		if (!FunctionManager::IsInitialized)
			FunctionManager::Initialize();
		if (!HookManager::IsInitialized)
			HookManager::Initialize();

		ScriptManager::Release();
		ScriptManager::Initialize();
	}


	void Initialize()
	{
		SpawnServer = reinterpret_cast<SpawnServerPrototype>(HookManager::Internal::DetourFunction(reinterpret_cast<BYTE*>(0x004FB7B0), reinterpret_cast<BYTE*>(&HookedSpawnServer), 0x5));
	}
}
