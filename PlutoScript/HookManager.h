#pragma once
#include "Datatypes.h"
#include <vector>

namespace HookManager
{	
	using OnSay = void(__cdecl*)(Entity* entity, int team, std::string message);
	using OnConnect = void(__cdecl*)(Entity* entity);
	using OnDisconnect = void(__cdecl*)(Entity* entity);
	using OnPlayerKilled = void(__cdecl*)(Entity* playerWhoDied, Entity* inflictor, Entity* playerWhoKilled, int* damage, int* mod, int* weaponIndex, bool* alternateWeapon, Vector3D direction, int* hitLocation);
	using OnPlayerDamaged = void(__cdecl*)(Entity* playerWhoWasDamaged, Entity* inflictor, Entity* playerWhoDamaged, int* damage, int* mod, int* weaponIndex, bool* alternateWeapon, Vector3D direction, int* hitLocation);

	namespace Internal
	{
		void* DetourFunction(BYTE* src, BYTE* dst, const int len);
		
		extern std::vector<OnSay> OnSayCallbacks;
		extern std::vector<OnConnect> OnConnectCallbacks;
		extern std::vector<OnDisconnect> OnDisconnectCallbacks;
		extern std::vector<OnPlayerKilled> OnPlayerKilledCallbacks;
		extern std::vector<OnPlayerDamaged> OnPlayerDamagedCallbacks;


		using OnSayNative = void(__cdecl*)(Entity* entity, int team, char* message);
		extern OnSayNative OnSayReturn;
		void HookedOnSay(Entity* entity, int team, char* message);

		using OnNotifyNative = void(__cdecl*)(int object, int notify, int a1);
		extern OnNotifyNative OnNotifyReturn;
		void HookedOnNotify(int object, int notify, int a1);

		using OnPlayerKilledNative = void(__cdecl*)(Entity* playerWhoDied, Entity* inflictor, Entity* playerWhoKilled, int damage, int mod, int weaponIndex, bool alternateWeapon, Vector3D direction, int hitLocation, int a1, int a2);
		extern OnPlayerKilledNative OnPlayerKilledReturn;
		void HookedOnPlayerKilled(Entity* playerWhoDied, Entity* inflictor, Entity* playerWhoKilled, int damage, int mod, int weaponIndex, bool alternateWeapon, Vector3D direction, int hitLocation,int a1, int a2);

		using OnPlayerDamagedNative = void(__cdecl*)(Entity* playerWhoWasDamaged, Entity* inflictor, Entity* playerWhoDamaged, int damage, int a1, int mod, int weaponIndex, bool alternateWeapon, Vector3D direction, int a2, int hitLocation, int a3);
		extern OnPlayerDamagedNative OnPlayerDamagedReturn;
		void HookedOnPlayerDamaged(Entity* playerWhoWasDamaged, Entity* inflictor, Entity* playerWhoDamaged, int damage, int a1, int mod, int weaponIndex, bool alternateWeapon, Vector3D direction, int a2, int hitLocation, int a3);
	}

	extern bool IsInitialized;
	void Initialize();
}

namespace PlutoniumScript
{
	__declspec(dllexport) void InstallOnSay(HookManager::OnSay onSay);
	__declspec(dllexport) void InstallOnConnect(HookManager::OnConnect onConnect);
	__declspec(dllexport) void InstallOnDisconnect(HookManager::OnDisconnect onDisconnect);
	__declspec(dllexport) void InstallOnPlayerKilled(HookManager::OnPlayerKilled onPlayerKilled);
	__declspec(dllexport) void InstallOnPlayerDamaged(HookManager::OnPlayerDamaged onPlayerDamaged);
}