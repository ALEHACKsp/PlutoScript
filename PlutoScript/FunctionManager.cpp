#include "stdafx.h"
FunctionManager::Internal::SendServerCommandPrototype FunctionManager::Internal::SendServerCommand;
FunctionManager::Internal::SystemPrintPrototype FunctionManager::Internal::SystemPrint;
FunctionManager::Internal::GetEntityFromObjectReferencePrototype FunctionManager::Internal::GetEntityFromObjectReference;
bool FunctionManager::IsInitialized = false;

namespace FunctionManager
{
	void Initialize()
	{
		Internal::SendServerCommand = reinterpret_cast<Internal::SendServerCommandPrototype>(0x004FD8E0);
		Internal::SystemPrint = reinterpret_cast<Internal::SystemPrintPrototype>(0x004D8E80);
		Internal::GetEntityFromObjectReference = reinterpret_cast<Internal::GetEntityFromObjectReferencePrototype>(0x004B18E0);

		IsInitialized = true;
	}
}

namespace PlutoniumScript
{

	__declspec(dllexport) void WriteToServerConsole(std::string message)
	{
		FunctionManager::Internal::SystemPrint(message.c_str());
	}

	__declspec(dllexport) void WriteToChat(std::string message)
	{
		FunctionManager::Internal::SendServerCommand(0, 0, "%c \"\x15%s\"", 84, message.c_str());
	}
}