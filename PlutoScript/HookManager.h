#pragma once
#include "Datatypes.h"
#include <vector>

namespace HookManager
{	
	using OnSay = void(__cdecl*)(Entity* entity, int team, std::string message);
	using OnConnect = void(__cdecl*)(Entity* entity);
	using OnDisconnect = void(__cdecl*)(Entity* entity);
	using OnPlayerKilled = void(__cdecl*)(Entity* playerWhoDied, Entity* inflictor, Entity* playerWhoKilled, int* damage, int* mod, int* weaponIndex, bool* alternateWeapon, Vector3D direction, int* hitLocation);

	namespace Internal
	{
		void* DetourFunction(BYTE* src, BYTE* dst, const int len);
		
		extern std::vector<OnSay> OnSayCallbacks;
		extern std::vector<OnConnect> OnConnectCallbacks;
		extern std::vector<OnDisconnect> OnDisconnectCallbacks;
		extern std::vector<OnPlayerKilled> OnPlayerKilledCallbacks;


		using OnSayNative = void(__cdecl*)(Entity* entity, int team, char* message);
		extern OnSayNative OnSayReturn;
		void HookedOnSay(Entity* entity, int team, char* message);

		using OnNotifyNative = void(__cdecl*)(int object, int notify, int a1);
		extern OnNotifyNative OnNotifyReturn;
		void HookedOnNotify(int object, int notify, int a1);

		using OnPlayerKilledNative = void(__cdecl*)(Entity* playerWhoDied, Entity* inflictor, Entity* playerWhoKilled, int damage, int mod, int weaponIndex, bool alternateWeapon, Vector3D direction, int a1,int hitLocation,int a2);
		extern OnPlayerKilledNative OnPlayerKilledReturn;
		void HookedOnPlayerKilled(Entity* playerWhoDied, Entity* inflictor, Entity* playerWhoKilled, int damage, int mod, int weaponIndex, bool alternateWeapon, Vector3D direction, int a1, int hitLocation, int a2);
	}

	extern bool IsInitialized;
	void Initialize();

	__declspec(dllexport) void InstallOnSay(OnSay onSay);
	__declspec(dllexport) void InstallOnConnect(OnConnect onConnect);
	__declspec(dllexport) void InstallOnDisconnect(OnDisconnect onDisconnect);
	__declspec(dllexport) void InstallOnPlayerKilled(OnPlayerKilled onPlayerKilled);
}
