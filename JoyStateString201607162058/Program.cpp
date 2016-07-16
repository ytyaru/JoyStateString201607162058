#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "GdiPlus.lib")
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>
#include <sti.h>
#include <gdiplus.h>
#include "JoyStateString.h"
#include "JoyCapsString.h"
#include "JoyInfoExString.h"
using namespace Gdiplus;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("JoyStateString201607162058");
HWND hWnd;

JOYINFOEX joyInfoEx;
JOYCAPS joyCaps;

GdiplusStartupInput gdiSI;
ULONG_PTR gdiToken;
Bitmap* gOffScreenBitmap;
Graphics* gOffScreenGraphics;

JoyStateString joyStateString;
JoyCapsString joyCapsString;
JoyInfoExString joyInfoExString;

unsigned int showJoystickId = JOYSTICKID1;

void DebugOut(const TCHAR* format, ...)
{
	TCHAR debugStr[1024];
	memset(debugStr, '\0', 1024);

	va_list arg;
	va_start(arg, format);
	_vstprintf_s(debugStr, 1024, format, arg);
	OutputDebugString(debugStr);
	va_end(arg);
}

void JoyLoop()
{
	joyInfoEx.dwSize = sizeof(JOYINFOEX);
	joyInfoEx.dwFlags = JOY_RETURNALL;
	MMRESULT res = joyGetPosEx(showJoystickId, &joyInfoEx);

	if (JOYERR_NOERROR != res) {
		memset(&joyInfoEx, 0, sizeof(joyInfoEx));
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
	GdiplusStartup(&gdiToken, &gdiSI, NULL);

	MSG msg;
	WNDCLASS myProg;

	if (!hPreInst) {
		myProg.style			= CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc		= WndProc;
		myProg.cbClsExtra		= 0;
		myProg.cbWndExtra		= 0;
		myProg.hInstance		= hInstance;
		myProg.hIcon			= NULL;
		myProg.hCursor			= LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		myProg.lpszMenuName		= NULL;
		myProg.lpszClassName	= szClassName;
		if (!RegisterClass(&myProg)) { return FALSE; }
	}
	hWnd = CreateWindow(szClassName,	// class名
		_T("JoyCaps, JoyInfoEx, 構造体を画面に表示する。JoyStick(GamePad)が必要。キーボードの←,→キーで表示するJoyStick切替。"),		// タイトル
		WS_OVERLAPPEDWINDOW,		// Style
		CW_USEDEFAULT,				// X
		CW_USEDEFAULT,				// Y
		GetSystemMetrics(SM_CXSCREEN),				// Width
		GetSystemMetrics(SM_CYSCREEN),				// Height
		NULL,						// 親ウィンドウまたはオーナーウィンドウのハンドル
		NULL,						// メニューハンドルまたは子ウィンドウ ID
		hInstance,					// アプリケーションインスタンスのハンドル
		NULL						// ウィンドウ作成データ
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Joystick
	joyInfoEx.dwSize = sizeof(JOYINFOEX);
	joyInfoEx.dwFlags = JOY_RETURNALL;
	int joystickNum = joyGetNumDevs();
	DebugOut(_T("Joystickサポート数:%d\n"), joyGetNumDevs());
	
	for(int i=0; i<joystickNum; i++){
		if (JOYERR_NOERROR == joyGetPosEx(i, &joyInfoEx)) {
			DebugOut(_T("ジョイスティック No.%d　接続されています\n"), i);
		}
	}

	// JoyCaps
	joyGetDevCaps(showJoystickId, &joyCaps, sizeof(joyCaps));
	DebugOut(joyCapsString.ToString(&joyCaps).c_str());
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		JoyLoop();
		InvalidateRect(hWnd, 0, false);
	}

	GdiplusShutdown(gdiToken);

	return (msg.wParam);
}

void OnPaint(HDC hdc)
{
	Graphics g(hdc);
	
	gOffScreenGraphics->Clear(Color::White);

	Gdiplus::SolidBrush* redBrush = new Gdiplus::SolidBrush(Gdiplus::Color::Red);
	gOffScreenGraphics->FillRectangle(redBrush, (150 + (20 * showJoystickId)), 40, 20, 12);
	delete redBrush;

	Gdiplus::Font fontJoyState(L"ＭＳ ゴシック", 9);
	Gdiplus::Font fontJoyCaps(L"ＭＳ ゴシック", 12);
	Gdiplus::Font fontJoyInfoEx(L"ＭＳ ゴシック", 30);
	Gdiplus::SolidBrush blackBrush(Color(255, 0, 0, 0));
	Gdiplus::StringFormat format;
	format.SetAlignment(StringAlignmentNear);
	
	Gdiplus::StringFormat formatState;
	formatState.SetAlignment(StringAlignmentNear);

	REAL* tabMargins = (REAL*) malloc(sizeof(REAL) * (joyGetNumDevs() + 1));
	tabMargins[0] = 150;
	for (unsigned int i = 1; i < joyGetNumDevs() + 1; i++) { tabMargins[i] = 20; }
	formatState.SetTabStops(0, (joyGetNumDevs() + 1), tabMargins);
	free(tabMargins);
	
	gOffScreenGraphics->DrawString(
		joyStateString.ToString().c_str(),
		-1, 
		&fontJoyState, 
		RectF(0.0f, 0.0f, (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN)), 
		&format, 
		&blackBrush);

	basic_stringstream<TCHAR> stream;
	stream << _T("表示JoystickID:") << showJoystickId;
	gOffScreenGraphics->DrawString(
		stream.str().c_str(),
		-1, 
		&fontJoyState, 
		RectF(0.0f, 24.0f, (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN)), 
		&format, 
		&blackBrush);

	gOffScreenGraphics->DrawString(
		joyStateString.ToStateTabSplitString().c_str(),
		-1, 
		&fontJoyState, 
		RectF(0.0f, 40.0f, (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN)), 
		&formatState, 
		&blackBrush);

	gOffScreenGraphics->DrawString(
		joyCapsString.ToString(&joyCaps).c_str(),
		-1, 
		&fontJoyCaps, 
		RectF(0.0f, 100.0f, (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN)), 
		&format, 
		&blackBrush);
	
	gOffScreenGraphics->DrawString(
		joyInfoExString.ToString(&joyInfoEx).c_str(),
		-1, 
		&fontJoyInfoEx, 
		RectF((float)GetSystemMetrics(SM_CXSCREEN) / 2, 100.0f, (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN)), 
		&format, 
		&blackBrush);

	g.DrawImage(gOffScreenBitmap, 0, 0);
	
	return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg) {
		case WM_CREATE:
			gOffScreenBitmap = new Bitmap(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			gOffScreenGraphics = Graphics::FromImage(gOffScreenBitmap);
			break;
		case WM_DEVICECHANGE:
			// デバイスの状態が変化した(USBポートへの抜き挿し、DVDドライブにCD-ROMを入れたとき等)
			joyGetDevCaps(showJoystickId, &joyCaps, sizeof(joyCaps));
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			OnPaint(hdc);
			EndPaint(hWnd, &ps);
			break;
		case WM_KEYDOWN:
			if (VK_LEFT == wParam) {
				if (JOYSTICKID1 < showJoystickId) { showJoystickId--; joyGetDevCaps(showJoystickId, &joyCaps, sizeof(joyCaps)); JoyLoop(); InvalidateRect(hWnd, 0, false); }
				OutputDebugString(_T("←キー押下した！"));
			} else if (VK_RIGHT == wParam) {
				if (showJoystickId < JOYSTICKID1 + (joyGetNumDevs() - 1)) { showJoystickId++; joyGetDevCaps(showJoystickId, &joyCaps, sizeof(joyCaps)); JoyLoop(); InvalidateRect(hWnd, 0, false); }
			}
		case WM_ERASEBKGND:
			return TRUE;
		case WM_DESTROY:
			// ダブルバッファ削除
			gOffScreenGraphics->Flush();
			delete gOffScreenBitmap;
			delete gOffScreenGraphics;
			PostQuitMessage(0);
			break;
		default:
			return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}
