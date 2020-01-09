#pragma once
#include "BaseWindow.h"

class Mainwindow : public BaseWindow<Mainwindow>
{
public:
	const TCHAR* ClassName()
	{
		return L"HolaWin";
	}
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};