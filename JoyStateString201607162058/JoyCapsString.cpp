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
	// Manufacturer Identifiers�i������ID�j
	// https://msdn.microsoft.com/ja-jp/library/windows/desktop/dd757147(v=vs.85).aspx
	// C:\Program Files\Microsoft SDKs\Windows\v7.1\Include
	// MMReg.h
	tstring str;
	if (joyCaps->wMid == MM_LOGITECH) { str += _T("Logitech, Inc.\n"); }
	if (joyCaps->wMid == 1133) { str += _T("Logicool, Inc.\n"); } // Logicool DUAL Action�f�o�C�X�̎��@�łŏo�����l�BWindows XP�W���h���C�o�B��p�h���C�o��SetPoint�͎g���Ă��Ȃ��B

	// �Ō��1�������폜����
	if (0 < str.length()) { str.erase( --str.end() ); }

	return str;
}
tstring JoyCapsString::ToStringPid(JOYCAPS* joyCaps)
{
	// Product Identifiers�i���iID�j
	// https://msdn.microsoft.com/ja-jp/library/windows/desktop/dd798609(v=vs.85).aspx
	// C:\Program Files\Microsoft SDKs\Windows\v7.1\Include
	// MMReg.h
	tstring str;
	if (joyCaps->wPid == 49686) { str += _T("Logicool DUAL ACTION\n"); } // Logicool DUAL Action�f�o�C�X�̎��@�ŏo�����l�B�����Ӗ�����̂������ς�킩��Ȃ��BWindows XP�W���h���C�o�B��p�h���C�o��SetPoint�͎g���Ă��Ȃ��B

	// �Ō��1�������폜����
	if (0 < str.length()) { str.erase( --str.end() ); }

	return str;
}
tstring JoyCapsString::ToStringCaps(JOYCAPS* joyCaps)
{
	tstring str;
	if (joyCaps->wCaps & JOYCAPS_HASZ) { str += _T("�E�W���C�X�e�B�b�N�́AZ���W���(��3��)��L���Ă��܂�\n"); }
	if (joyCaps->wCaps & JOYCAPS_HASR) { str += _T("�E�W���C�X�e�B�b�N�́AR���W���(��4��)��L���Ă��܂�\n"); }
	if (joyCaps->wCaps & JOYCAPS_HASU) { str += _T("�E�W���C�X�e�B�b�N�́AU���W���(��5��)��L���Ă��܂�\n"); }
	if (joyCaps->wCaps & JOYCAPS_HASV) { str += _T("�E�W���C�X�e�B�b�N�́AV���W���(��6��)��L���Ă��܂�\n"); }
	if (joyCaps->wCaps & JOYCAPS_HASPOV) { str += _T("�E�W���C�X�e�B�b�N�́APOV(Point Of View)�̏��������Ă��܂�\n"); }
	if (joyCaps->wCaps & JOYCAPS_POV4DIR) { str += _T("�E�W���C�X�e�B�b�N��POV(Point Of View)�́A���U�l�i���S�A�O�A��A���A�E�j���T�|�[�g���Ă��܂�\n"); }
	if (joyCaps->wCaps & JOYCAPS_POVCTS) { str += _T("�E�W���C�X�e�B�b�N��POV(Point Of View)�́A�A���x�̃x�A�����O���T�|�[�g���Ă��܂�\n"); }
	
	// �Ō��1�������폜����
	if (0 < str.length()) { str.erase( --str.end() ); }

	return str;
}
