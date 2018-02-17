#pragma once
namespace FunctionManager
{
	namespace Internal
	{
		using SendServerCommandPrototype = DWORD(__cdecl*)(int a1, int a2, const char* msg, ...);
		extern SendServerCommandPrototype SendServerCommand;
		using SystemPrintPrototype = void(__cdecl*)(const char* msg);
		extern SystemPrintPrototype SystemPrint;
	}

	extern bool IsInitialized;
	void Initialize();
	__declspec(dllexport) void WriteToServerConsole(std::string message);
	__declspec(dllexport) void WriteToChat(std::string message);
}