#include "stdafx.h"
FunctionManager::Internal::SendServerCommandPrototype FunctionManager::Internal::SendServerCommand;
FunctionManager::Internal::SystemPrintPrototype FunctionManager::Internal::SystemPrint;
bool FunctionManager::IsInitialized = false;

namespace FunctionManager
{
	void Initialize()
	{
		Internal::SendServerCommand = reinterpret_cast<Internal::SendServerCommandPrototype>(0x004FD8E0);
		Internal::SystemPrint = reinterpret_cast<Internal::SystemPrintPrototype>(0x004D8E80);
		IsInitialized = true;
	}

	__declspec(dllexport) void WriteToServerConsole(std::string message)
	{
		Internal::SystemPrint(message.c_str());
	}

	__declspec(dllexport) void WriteToChat(std::string message)
	{
		Internal::SendServerCommand(0, 0, "%c \"\x15%s\"", 84, message.c_str());
	}
}