#include "JoyStateString.h"

JoyStateString::JoyStateString(void)
{
}

JoyStateString::~JoyStateString(void)
{
}

tstring JoyStateString::ToString()
{
	tstringstream stream;

	stream << _T("Joystickサポート数:") << joyGetNumDevs() << endl <<
		_T("接続JoystickID:") << GetActiveJoystickIdString() << endl;

	return stream.str();
}
 
//						 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
//MMSYSERR_NODRIVER		   ××××××××××××××××××××××
//MMSYSERR_INVALPARAM	   ××××××××××××××××××××××
//MMSYSERR_BADDEVICEID	   ××××××××××××××××××××××
//JOYERR_UNPLUGGED		   ××××××××××××××××××××××
tstring JoyStateString::ToStateTabSplitString()
{
	unsigned int supportJoystickNum = joyGetNumDevs();

	MMRESULT* mmResults = (MMRESULT*) malloc(sizeof(MMRESULT) * supportJoystickNum);
	memset(mmResults, 0, sizeof(MMRESULT) * supportJoystickNum);

	JOYINFOEX joyInfoEx;
	joyInfoEx.dwSize = sizeof(JOYINFOEX);
	joyInfoEx.dwFlags = JOY_RETURNALL;
	// i = JOYSTICKID1 = 0
	for (unsigned int i=JOYSTICKID1; i<supportJoystickNum; i++) {
		mmResults[i] = joyGetPosEx(i, &joyInfoEx);
	}

	tstring str = this->MakeTabSplitString(mmResults, supportJoystickNum);

	free(mmResults);
	mmResults = NULL;

	return str;
}

tstring JoyStateString::MakeTabSplitString(MMRESULT* mmResults, unsigned int supportJoystickNum)
{
	tstringstream stream;
	
	// ヘッダ
	stream << _T("エラー種別") << _T("\t");
	for (unsigned int i=0; i<supportJoystickNum; i++) {
		stream << i;
		if (i < supportJoystickNum - 1) { stream << _T("\t"); }
	}
	stream << endl;

	// ジョイスティックドライバが存在しません。
	stream << _T("MMSYSERR_NODRIVER") << _T("\t");
	for (unsigned int i=0; i<supportJoystickNum; i++) {
		if (mmResults[i] & MMSYSERR_NODRIVER) {
			stream << _T("×");
		} else {
			stream << _T("  ");
		}
		if (i < supportJoystickNum - 1) { stream << _T("\t"); }
	}
	stream << endl;
	
	// 無効なパラメータが渡されました。
	stream << _T("MMSYSERR_INVALPARAM") << _T("\t");
	for (unsigned int i=0; i<supportJoystickNum; i++) {
		if (mmResults[i] & MMSYSERR_INVALPARAM) {
			stream << _T("×");
		} else {
			stream << _T("  ");
		}
		if (i < supportJoystickNum - 1) { stream << _T("\t"); }
	}
	stream << endl;
	
	// 指定されたジョイスティック識別子は無効です。
	stream << _T("MMSYSERR_BADDEVICEID") << _T("\t");
	for (unsigned int i=0; i<supportJoystickNum; i++) {
		if (mmResults[i] & MMSYSERR_BADDEVICEID) {
			stream << _T("×");
		} else {
			stream << _T("  ");
		}
		if (i < supportJoystickNum - 1) { stream << _T("\t"); }
	}
	stream << endl;

	// 指定されたジョイスティックはシステムに接続されていません。
	stream << _T("JOYERR_UNPLUGGED") << _T("\t");
	for (unsigned int i=0; i<supportJoystickNum; i++) {
		if (mmResults[i] & JOYERR_UNPLUGGED) {
			stream << _T("×");
		} else {
			stream << _T("  ");
		}
		if (i < supportJoystickNum - 1) { stream << _T("\t"); }
	}
	//stream << endl;

	return stream.str();
}

tstring JoyStateString::GetActiveJoystickIdString()
{
	tstringstream stream;
	
	JOYINFOEX joyInfoEx;
	joyInfoEx.dwSize = sizeof(JOYINFOEX);
	joyInfoEx.dwFlags = JOY_RETURNALL;
	for(unsigned int i=0; i<joyGetNumDevs(); i++){
		if (JOYERR_NOERROR == joyGetPosEx(i, &joyInfoEx)) {
			stream << i << _T(",");
		}
	}

	tstring str = stream.str();
	if (0 < str.length()) {
		str.erase( --str.end()) ;
	}
	return str;
}
