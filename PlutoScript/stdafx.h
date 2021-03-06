// stdafx.h: Includedatei für Standardsystem-Includedateien
// oder häufig verwendete projektspezifische Includedateien,
// die nur in unregelmäßigen Abständen geändert werden.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Komponenten aus Windows-Headern ausschließen
// Windows-Headerdateien:
#include <windows.h>

#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "PlutoScript.h"
#include "ScriptManager.h"
#include "Script.h"
#include "HookManager.h"
#include "Datatypes.h"
#include "FunctionManager.h"
