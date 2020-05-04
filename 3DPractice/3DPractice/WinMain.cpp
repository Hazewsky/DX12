#include <Windows.h>

LRESULT /*depends on the msg*/ CALLBACK CustomWndProc
(  
	HWND hWnd /*handle to a window we'll process msgs for */,
	UINT msg /*msg ID*/,
	WPARAM wParam /*additional info based on msg*/,
	LPARAM lParam /*additional info based on msg*/
)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain( //CALLBACK - _stdcall, pass params on the stack
	HINSTANCE hInstance, //pointers to structures that hold info about the program(where is loaded into memory, etc)
	HINSTANCE hPrevInstance, //always NULL
	LPSTR lpCmdLine, //command line
	int nCmdSHow) // how winsow should be shown after it was created
{
	const auto pClassName = "MainController";
	const auto pWindowName = "Butthurt";
	//register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc); //cb size: structure size in bytes
	wc.style = CS_OWNDC; // //style: windows style. context
	wc.lpfnWndProc = CustomWndProc;
	//lpfnWndProc: ptr to the func that is going to handle all the messages, determine the behaviour of the window, how the window looks
	//DefWindowProc -> default procedure
	wc.cbClsExtra = 0;//cbClsExtra - extra bytes for class
	wc.cbWndExtra = 0;//cbWndExtra - extra bytes for win
	wc.hInstance = hInstance;
	wc.hIcon = nullptr; //hIcon - class icon
	wc.hIconSm = nullptr;//hIconSm - favicon
	wc.hCursor = nullptr;//hCursor - cursor
	wc.hbrBackground = nullptr;//hbrBackground - brush (repaint the entire window)
	wc.lpszMenuName = nullptr;//lpszMenuName - window name for menus
	wc.lpszClassName = pClassName;//lpszClassName - class name (used when create windows of the class type
	//use new function
	RegisterClassEx(&wc);
	//create window instance
	HWND window = CreateWindowExA(
		0,//dwExStyle - style (only for ex version of the function), 0 - no styles
		pClassName,//lpClassName - class name
		pWindowName,//lpWindowName - window name
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,//dwStyle - normal window style
		200,//X - posX
		200,//Y - posY
		640,//nWidth - dimensionX
		480,//wHeight - dimensionY
		nullptr,//hWndParent - handle to the parent
		nullptr,//hMenu - handle to the menu
		hInstance,//hInstance - out instance
		nullptr//lpParam - parameter to configure custom data that can be passed to a window
		);
	//show window
	ShowWindow(
		window,//window
		SW_SHOW//the command
	);
	MSG msg;
	BOOL gResult;
	//return: WM_QUIT - zero, ERROR - 1, else - nonzero
	while ((gResult = GetMessage(
		&msg,//pointer to  (MSG) structure
		NULL,//window. NULL to get message from any window
		0,//MSG filter min, 0 - catch all MSGs
		0//MSG filter max
		)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
	
	
	
	return 0;
}