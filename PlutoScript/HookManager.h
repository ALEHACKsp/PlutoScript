#pragma once
#include "Datatypes.h"
#include <vector>


namespace HookManager
{	
	using OnSay = void(_cdecl*)(Entity* entity, int team, std::string message);

	namespace Internal
	{
		void* DetourFunction(BYTE* src, BYTE* dst, const int len);
		
		using OnSayNative = void(__cdecl*)(Entity* entity, int team, char* message);
		extern std::vector<OnSay> OnSayCallbacks;
		extern OnSayNative OnSayReturn;
		void HookedOnSay(Entity* entity, int team, char* message);

	}

	extern bool IsInitialized;
	void Initialize();

	__declspec(dllexport) void InstallOnSay(OnSay onSay);
}
