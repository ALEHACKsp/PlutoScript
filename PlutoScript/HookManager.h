#pragma once
#include "Datatypes.h"
#include <vector>

namespace HookManager
{	
	using OnSay = void(__cdecl*)(Entity* entity, int team, std::string message);
	using OnConnect = void(__cdecl*)(Entity* entity);
	using OnDisconnect = void(__cdecl*)(Entity* entity);

	namespace Internal
	{
		void* DetourFunction(BYTE* src, BYTE* dst, const int len);
		
		using OnSayNative = void(__cdecl*)(Entity* entity, int team, char* message);
		extern std::vector<OnSay> OnSayCallbacks;
		extern OnSayNative OnSayReturn;
		void HookedOnSay(Entity* entity, int team, char* message);

		void ExecEntThreadNumHelper(int functionHandle, int objectReference);

		extern std::vector<OnConnect> OnConnectCallbacks;
		extern std::vector<OnDisconnect> OnDisconnectCallbacks;
	}

	extern bool IsInitialized;
	void Initialize();

	__declspec(dllexport) void InstallOnSay(OnSay onSay);
	__declspec(dllexport) void InstallOnConnect(OnConnect onConnect);
	__declspec(dllexport) void InstallOnDisconnect(OnDisconnect onDisconnect);
}
