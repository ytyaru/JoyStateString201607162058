#include "JoyCapsString.h"

JoyCapsString::JoyCapsString(void)
{
}

JoyCapsString::~JoyCapsString(void)
{
}

tstring JoyCapsString::ToString(JOYCAPS* joyCaps)
{
	tstringstream stream;
	
	stream << _T("----- JOYCAPS -----") << endl << 
		_T("wMid:") << joyCaps->wMid << " \"" << ToStringMid(joyCaps) << "\"" << endl <<
		_T("wPid:") << joyCaps->wPid << " \"" << ToStringPid(joyCaps) << "\"" << endl <<
		_T("szPname:") << joyCaps->szPname << endl <<
		_T("wXmin:") << joyCaps->wXmin << endl <<
		_T("wXmax:") << joyCaps->wXmax << endl <<
		_T("wYmin:") << joyCaps->wYmin << endl <<
		_T("wYmax:") << joyCaps->wYmax << endl <<
		_T("wZmin:") << joyCaps->wZmin << endl <<
		_T("wZmax:") << joyCaps->wZmax << endl <<
		_T("wNumButtons:") << joyCaps->wNumButtons << endl <<
		_T("wPeriodMin:") << joyCaps->wPeriodMin << endl <<
		_T("wPeriodMax:") << joyCaps->wPeriodMax << endl <<
		_T("wRmin:") << joyCaps->wRmin << endl <<
		_T("wRmax:") << joyCaps->wRmax << endl <<
		_T("wUmin:") << joyCaps->wUmin << endl <<
		_T("wUmax:") << joyCaps->wUmax << endl <<
		_T("wVmin:") << joyCaps->wVmin << endl <<
		_T("wVmax:") << joyCaps->wVmax << endl <<
		_T("wCaps:") << joyCaps->wCaps << endl <<
		ToStringCaps(joyCaps) << endl <<
		_T("wMaxAxes:") << joyCaps->wMaxAxes << endl <<
		_T("wNumAxes:") << joyCaps->wNumAxes << endl <<
		_T("wMaxButtons:") << joyCaps->wMaxButtons << endl <<
		_T("szRegKey:") << joyCaps->szRegKey << endl <<
		_T("szOEMVxD:") << joyCaps->szOEMVxD << endl;

	return stream.str();
}

tstring JoyCapsString::ToStringMid(JOYCAPS* joyCaps)
{
	// Manufacturer Identifiers（製造者ID）
	// https://msdn.microsoft.com/ja-jp/library/windows/desktop/dd757147(v=vs.85).aspx
	// C:\Program Files\Microsoft SDKs\Windows\v7.1\Include
	// MMReg.h
	tstring str;
	if (joyCaps->wMid == MM_LOGITECH) { str += _T("Logitech, Inc.\n"); }
	if (joyCaps->wMid == 1133) { str += _T("Logicool, Inc.\n"); } // Logicool DUAL Actionデバイスの実機でで出た数値。Windows XP標準ドライバ。専用ドライバのSetPointは使っていない。

	// 最後の1文字を削除する
	if (0 < str.length()) { str.erase( --str.end() ); }

	return str;
}
tstring JoyCapsString::ToStringPid(JOYCAPS* joyCaps)
{
	// Product Identifiers（製品ID）
	// https://msdn.microsoft.com/ja-jp/library/windows/desktop/dd798609(v=vs.85).aspx
	// C:\Program Files\Microsoft SDKs\Windows\v7.1\Include
	// MMReg.h
	tstring str;
	if (joyCaps->wPid == 49686) { str += _T("Logicool DUAL ACTION\n"); } // Logicool DUAL Actionデバイスの実機で出た数値。何を意味するのかさっぱりわからない。Windows XP標準ドライバ。専用ドライバのSetPointは使っていない。

	// 最後の1文字を削除する
	if (0 < str.length()) { str.erase( --str.end() ); }

	return str;
}
tstring JoyCapsString::ToStringCaps(JOYCAPS* joyCaps)
{
	tstring str;
	if (joyCaps->wCaps & JOYCAPS_HASZ) { str += _T("・ジョイスティックは、Z座標情報(第3軸)を有しています\n"); }
	if (joyCaps->wCaps & JOYCAPS_HASR) { str += _T("・ジョイスティックは、R座標情報(第4軸)を有しています\n"); }
	if (joyCaps->wCaps & JOYCAPS_HASU) { str += _T("・ジョイスティックは、U座標情報(第5軸)を有しています\n"); }
	if (joyCaps->wCaps & JOYCAPS_HASV) { str += _T("・ジョイスティックは、V座標情報(第6軸)を有しています\n"); }
	if (joyCaps->wCaps & JOYCAPS_HASPOV) { str += _T("・ジョイスティックは、POV(Point Of View)の情報を持っています\n"); }
	if (joyCaps->wCaps & JOYCAPS_POV4DIR) { str += _T("・ジョイスティックのPOV(Point Of View)は、離散値（中心、前、後、左、右）をサポートしています\n"); }
	if (joyCaps->wCaps & JOYCAPS_POVCTS) { str += _T("・ジョイスティックのPOV(Point Of View)は、連続度のベアリングをサポートしています\n"); }
	
	// 最後の1文字を削除する
	if (0 < str.length()) { str.erase( --str.end() ); }

	return str;
}
