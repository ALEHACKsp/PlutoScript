#pragma once
#include "Script.h"

namespace ScriptManager
{
	extern std::vector<Script> Scripts;

	namespace Internal
	{
		std::experimental::filesystem::path GetScriptFiles();
		void LoadScripts();
		void GetScriptEntryPoints();
		void ExecuteScripts();

	}

	extern bool IsInitialized;
	void Initialize();
}
