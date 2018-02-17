#include "stdafx.h"

Script::Script(std::string name, HMODULE module)
{
	Name = name;
	Module = module;
}

void Script::Execute()
{
	Entry();
	HasExecuted = true;
}
