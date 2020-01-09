#include "MainWindow.h"

LRESULT Mainwindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
