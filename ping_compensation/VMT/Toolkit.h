// the1domo's and Freaky's  Toolkit v3.0 for Game Hacking
#pragma once
#include <windows.h>
#include <process.h>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <dbghelp.h>
#include <shlobj.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <tlhelp32.h>
#include <intrin.h>

using namespace std;

namespace Toolkit
{
	extern char					fileDir[512];
	extern bool					isInitialized;
	extern bool					enableBreakpoints;
	extern bool					enableLogs;

	extern HANDLE				mainProcess;
	extern HMODULE				mainModule;
	extern HWND					mainWnd;
	extern char*				fileConfig;				//The config filename
	extern char*				fileLog;				//The log filename
	extern POINT				curPos;					//The current cursor pos

	void init( HMODULE hModule, char* windowName = NULL, bool breakpoints = false, bool logs = false );

	char*	getFullPath( char* filename );		//Get the full path of a file in the dll dir
	void	addLog( const char * fmt, ... );	//Add a message to the log file

	namespace Hook
	{
		void	readMemory( DWORD address, void* buffer, int size );								//Reads memory at a given address
		void	readMemory( HANDLE process, DWORD address, void* buffer, int size );				//Reads memory at a given address from an outside process
		void	writeMemory( DWORD address, void* buffer, int size );								//Writes memory at a given address

		DWORD	findPattern( DWORD startAddres, DWORD searchLength, BYTE* pattern, char mask[] );	//Scans memory for byte pattern and returns address
		DWORD	getModuleSize( LPSTR strModuleName );												//Gets the size of a module
		PBYTE	getModuleBase( LPSTR strModuleName );												//Gets the base address of a module
	}
};
