#pragma once
#include "Datatypes.h"
#include <vector>

namespace HookManager
{	
	using OnSay = void(_cdecl*)(Entity* entity, int team, char* message);

	namespace Internal
	{
		void* DetourFunction(BYTE* src, BYTE* dst, const int len);
		extern std::vector<OnSay> OnSayCallbacks;
		extern OnSay OnSayReturn;
		void HookedOnSay(Entity* entity, int team, char* message);

	}

	extern bool IsInitialized;
	void Initialize();

	__declspec(dllexport) void InstallOnSay(OnSay onSay);
}
