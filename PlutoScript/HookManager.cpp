#include "stdafx.h"
std::vector<HookManager::OnSay> HookManager::Internal::OnSayCallbacks;
HookManager::OnSay HookManager::Internal::OnSayReturn;
bool HookManager::IsInitialized = false;

namespace HookManager
{
	namespace Internal
	{
		void* DetourFunction(BYTE* src, BYTE* dst, const int len)
		{
			BYTE* jmp = (BYTE*)malloc(len + 5);
			DWORD dwBack;

			VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
			memcpy(jmp, src, len);

			jmp += len;
			jmp[0] = 0xE9;

			*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;

			src[0] = 0xE9;
			*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;
			for (int i = 5; i < len; i++)
				src[i] = 0x90;
			VirtualProtect(src, len, dwBack, &dwBack);

			return (jmp - len);
		}

		void HookedOnSay(Entity* entity, int team, char* message)
		{
			for (auto &callback : OnSayCallbacks)
				callback(entity, team, message);

			return OnSayReturn(entity, team, message);
		}
	}

	__declspec(dllexport) void InstallOnSay(OnSay onSay)
	{
		Internal::OnSayCallbacks.push_back(onSay);
	}

	void Initialize()
	{
		Internal::OnSayReturn = reinterpret_cast<OnSay>(Internal::DetourFunction(reinterpret_cast<BYTE*>(0x0047E900), reinterpret_cast<BYTE*>(Internal::HookedOnSay), 0x6));
		IsInitialized = true;
	}
}
