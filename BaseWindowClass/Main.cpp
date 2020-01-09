#include "MainWindow.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	Mainwindow win;

	win.Create(L"Mi ventana", WS_OVERLAPPEDWINDOW);

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = { 0 };
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return 0;
}