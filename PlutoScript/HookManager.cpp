#include "stdafx.h"
std::vector<HookManager::OnSay> HookManager::Internal::OnSayCallbacks;
HookManager::Internal::OnSayNative HookManager::Internal::OnSayReturn;

std::vector<HookManager::OnConnect> HookManager::Internal::OnConnectCallbacks;
std::vector<HookManager::OnDisconnect> HookManager::Internal::OnDisconnectCallbacks;

bool HookManager::IsInitialized = false;

//some magic
int functionHandle;
int objectReference;
int returnAdress = 0x004F0289;
__declspec(naked) void HookedExecEntThreadNum()
{
	__asm mov[functionHandle], eax;
	__asm mov[objectReference], ecx;

	__asm pushad;
	__asm pushfd;

	HookManager::Internal::ExecEntThreadNumHelper(functionHandle, objectReference);

	__asm popfd;
	__asm popad;

	__asm push ebp;
	__asm mov ebp, esp;
	__asm and esp, 0x0FFFFFFF8;
	__asm sub esp, 8;

	__asm jmp[returnAdress];
}

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

		void ExecEntThreadNumHelper(int functionHandle,int objectReference)
		{
			if (functionHandle == 412300)
				for (auto &callback : OnConnectCallbacks)
					callback(FunctionManager::Internal::GetEntityFromObjectReference(objectReference));
			if (functionHandle == 412332)
				for (auto &callback : OnDisconnectCallbacks)
					callback(FunctionManager::Internal::GetEntityFromObjectReference(objectReference));
		}
	}


	void Initialize()
	{
		Internal::OnSayReturn = reinterpret_cast<Internal::OnSayNative>(Internal::DetourFunction(reinterpret_cast<BYTE*>(0x0047E900), reinterpret_cast<BYTE*>(Internal::HookedOnSay), 0x6));
		Internal::DetourFunction(reinterpret_cast<BYTE*>(0x004F0280), reinterpret_cast<BYTE*>(HookedExecEntThreadNum), 0x6);

		IsInitialized = true;
	}

	__declspec(dllexport) void InstallOnSay(OnSay onSay)
	{
		Internal::OnSayCallbacks.push_back(onSay);
	}

	__declspec(dllexport) void InstallOnConnect(OnConnect onConnect)
	{
		Internal::OnConnectCallbacks.push_back(onConnect);
	}

	__declspec(dllexport) void InstallOnDisconnect(OnDisconnect onDisconnect)
	{
		Internal::OnDisconnectCallbacks.push_back(onDisconnect);
	}
}
