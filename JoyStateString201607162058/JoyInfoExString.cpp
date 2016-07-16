#include "JoyInfoExString.h"

JoyInfoExString::JoyInfoExString(void)
{
}


JoyInfoExString::~JoyInfoExString(void)
{
}

tstring JoyInfoExString::ToString(JOYINFOEX* joyInfoEx)
{
	tstringstream stream;
	stream << _T("----- JoyInfoEx -----") << endl <<
		_T("dwSize:") << joyInfoEx->dwSize << endl <<
		_T("dwFlags:") << joyInfoEx->dwFlags << endl <<
		_T("dwXpos:") << joyInfoEx->dwXpos << endl <<
		_T("dwYpos:") << joyInfoEx->dwYpos << endl <<
		_T("dwZpos:") << joyInfoEx->dwZpos << endl <<
		_T("dwRpos:") << joyInfoEx->dwRpos << endl <<
		_T("dwUpos:") << joyInfoEx->dwUpos << endl <<
		_T("dwVpos:") << joyInfoEx->dwVpos << endl <<
		_T("dwButtons:") << joyInfoEx->dwButtons << endl <<
		_T("dwButtonNumber:") << joyInfoEx->dwButtonNumber << endl <<
		_T("dwPOV:") << joyInfoEx->dwPOV << endl <<
		_T("dwReserved1:") << joyInfoEx->dwReserved1 << endl <<
		_T("dwReserved2:") << joyInfoEx->dwReserved2 << endl;
	return stream.str();
}