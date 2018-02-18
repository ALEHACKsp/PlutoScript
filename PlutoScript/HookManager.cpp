#include "stdafx.h"
std::vector<HookManager::OnSay> HookManager::Internal::OnSayCallbacks;
HookManager::Internal::OnSayNative HookManager::Internal::OnSayReturn;

std::vector<HookManager::OnConnect> HookManager::Internal::OnConnectCallbacks;
std::vector<HookManager::OnDisconnect> HookManager::Internal::OnDisconnectCallbacks;

std::vector<HookManager::OnPlayerKilled> HookManager::Internal::OnPlayerKilledCallbacks;
HookManager::Internal::OnPlayerKilledNative HookManager::Internal::OnPlayerKilledReturn;

HookManager::Internal::OnNotifyNative HookManager::Internal::OnNotifyReturn;

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

		void HookedOnPlayerKilled(Entity* playerWhoDied, Entity* inflictor, Entity* playerWhoKilled, int damage,
			int mod, int weaponIndex, bool alternateWeapon, Vector3D direction, int a1, int hitLocation, int a2)
		{
			for (auto &callback : OnPlayerKilledCallbacks)
				callback(playerWhoDied, inflictor, playerWhoKilled, &damage, &mod, &weaponIndex, &alternateWeapon, direction, &hitLocation);

			return OnPlayerKilledReturn(playerWhoDied, inflictor, playerWhoKilled, damage, mod, weaponIndex, alternateWeapon, direction, a1, hitLocation, a2);
		}

		void HookedOnNotify(int object, int notify, int a1)
		{
			if (object)
			{

				if (notify == 8907)
					for (auto &callback : OnConnectCallbacks)
						callback(FunctionManager::Internal::GetEntityFromObjectReference(object));
				if (notify == 3188 && a1 == 2 && reinterpret_cast<ScriptEnviorment*>(0x001F58080)->Top->Value.Integer == 1422)
				{
					for (auto &callback : OnDisconnectCallbacks)
						callback(FunctionManager::Internal::GetEntityFromObjectReference(object));
					//auto scriptEnv = reinterpret_cast<ScriptEnviorment*>(0x001F58080);
					//char buffer[1024];

					//auto x = scriptEnv->Top;
					//auto y = &scriptEnv->Top[-1];
					//auto z = &scriptEnv->Top[-2];
					//sprintf_s(buffer, "Menusresponse: InParams: %i | OutParams: %i \n Top_Type : %i | Top_Value : %i \n -1_Typ:e %i | -1_Value: %i \n -2_Type: %i | -2_Value : %i\n", scriptEnv->InParametersCount,scriptEnv->OutParametersCount,x->Type,x->Value.Integer,y->Type,y->Value.Integer,z->Type,z->Value.Integer);
					//FunctionManager::WriteToServerConsole(buffer);
				}
			}
			return OnNotifyReturn(object, notify, a1);
		}
	}

	void Initialize()
	{
		Internal::OnSayReturn = reinterpret_cast<Internal::OnSayNative>(Internal::DetourFunction(reinterpret_cast<BYTE*>(0x0047E900), reinterpret_cast<BYTE*>(Internal::HookedOnSay), 0x6));
		Internal::OnPlayerKilledReturn = reinterpret_cast<Internal::OnPlayerKilledNative>(Internal::DetourFunction(reinterpret_cast<BYTE*>(0x004AD030), reinterpret_cast<BYTE*>(Internal::HookedOnPlayerKilled), 0x6));
		Internal::OnNotifyReturn = reinterpret_cast<Internal::OnNotifyNative>(Internal::DetourFunction(reinterpret_cast<BYTE*>(0x004EFBB0), reinterpret_cast<BYTE*>(Internal::HookedOnNotify), 0x7));

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

	__declspec(dllexport) void InstallOnPlayerKilled(OnPlayerKilled onPlayerKilled)
	{
		Internal::OnPlayerKilledCallbacks.push_back(onPlayerKilled);
	}
}
