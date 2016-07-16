#pragma once
#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <MMReg.h>
// C:\Program Files\Microsoft SDKs\Windows\v7.1\Include
// https://msdn.microsoft.com/ja-jp/library/windows/desktop/dd757147(v=vs.85).aspx
using namespace std;

#ifndef basic_string_tchar_H
#define basic_string_tchar_H
typedef std::basic_stringstream<TCHAR> tstringstream;
typedef std::basic_string<TCHAR> tstring;
#endif // basic_string_tchar_H

class JoyInfoExString
{
public:
	JoyInfoExString(void);
	~JoyInfoExString(void);
	tstring ToString(JOYINFOEX* joyInfoEx);
};
