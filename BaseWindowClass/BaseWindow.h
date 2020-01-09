#pragma once
#include "VZWin.h"
#include <algorithm>
#include <cassert>

template <typename DERIVED_TYPE>
class BaseWindow
{
public:
	BaseWindow()
		:
		hWnd(nullptr), 
		hInst(GetModuleHandle(nullptr))
	{}
	HWND Window() const
	{
		return hWnd;
	}
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVED_TYPE* pThis = nullptr;
		
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreateStruct = (CREATESTRUCT*)lParam;
			pThis = (DERIVED_TYPE*)pCreateStruct->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
			pThis->hWnd = hWnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	void Create(const TCHAR* lpWndName, DWORD dwStyle, DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT,
		HWND hWndParent = nullptr, HMENU hMenu = nullptr) 
	{
		WNDCLASS wc = { 0 };
		
		wc.lpfnWndProc = StaticWndProc;
		wc.hInstance = hInst;
		wc.lpszClassName = ClassName();

		ATOM aReg = RegisterClass(&wc);

		assert(aReg != 0);

		hWnd = CreateWindowEx(dwExStyle, ClassName(), lpWndName, dwStyle, x, y, width, height, hWndParent,
			hMenu, hInst, this);

		assert(hWnd != nullptr);
	}
protected:
	HWND hWnd;
	HINSTANCE hInst = nullptr;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual const TCHAR* ClassName() = 0;
};