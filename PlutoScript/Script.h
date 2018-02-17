#pragma once
class Script
{
public:
	using EntryPoint = void(__cdecl*)();

	std::string Name;
	HMODULE Module;
	EntryPoint Entry;
	bool HasExecuted;


	Script(std::string name , HMODULE module);

	void Execute();
};

