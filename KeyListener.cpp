#include "Keylistener.h"
#include <iostream>
#include <Windows.h> // Keyboard input stuff.
#include <thread>

using std::cout; using std::endl;

bool KeepHookActive = true;

int P::KeyListener::ListenForKeys(std::vector<int>* Keys)
{
	// Return here if Keys collection is empty or invalid.
	if (Keys->size() <= 0)
	{
		cout << "Error: P::KeyListener::ListenForKeys - Keys collection is empty or invalid" << endl;
		return -1;
	}

	// Store the keys' reference here.
	P::KeyListener::Keys = Keys;

	//SetupHookLowLevel();

	Keyboard_HighLevelRead();

	//return KeyListenerLoop();

	return FoundKey;
}

int P::KeyListener::KeyListenerLoop()
{
	// Check here if list of keys is valid, else throw an error.
	if (Keys->size() <= 0)
	{
		cout << "Error: KeyListener - ListenForKeys: size of Keys collection is invalid";
		return -1;
	}


	bool ValidKeyListened = false;
	while (!ValidKeyListened)
	{
		for (int forKey : *Keys)
		{
			if (GetKeyState(forKey) & 0x8000)	// "& 0x8000" checks if high-order bit is set (1 << 15)
			{
				ValidKeyListened = true;
				return forKey;
			}
		}
	}
	return -1;
}








// Windows console application high-level input hook.

void P::KeyListener::Keyboard_HighLevelRead()
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	// Get the standard input handle.

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit.

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events.

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 20 input events.

	while (!KeyIsFound) //(counter++ <= 40)
	{
		// Wait for the events.

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead)) // number of records read
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler.

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events

			case MENU_EVENT:   // disregard menu events
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}
		}
	}

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);
}

void P::KeyListener::ErrorExit(LPCSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

void P::KeyListener::KeyEventProc(KEY_EVENT_RECORD ker)
{
	//printf("Key event: ");
	//
	//if (ker.bKeyDown)
	//	printf("key pressed\n");
	//else printf("key released\n");


	// Don't continue if it's not a key up event.
	if (!ker.bKeyDown) { return; }

	int Key = 0;
	int size = static_cast<int>(Keys->size());
	int last_element = size - 1;

	for (int i = 0; i <= last_element; i++)
	{
		Key = Keys->at(i);
		if (ker.wVirtualKeyCode == Key)
		{
			KeyIsFound = true;
			FoundKey = Key;
			break;
		}
	}
}

void P::KeyListener::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	printf("Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press \n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		else
		{
			printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		printf("vertical mouse wheel\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
}

void P::KeyListener::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}








// Windows keyboard low level hook.

HHOOK Handle_Hook{ NULL };

enum Keys_hook
{
	ShiftKey = 16,
	Capital = 20,
};

int shift_active()
{
	return GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0;
}

int capital_active()
{
	return (GetKeyState(VK_CAPITAL) & 1) == 1;
}

LRESULT CALLBACK LowLevelKeyboardProc(const int code, const WPARAM wParam, const LPARAM lParam)
{
	if (wParam == WM_KEYDOWN)
	{
		KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;
		DWORD wScanCode = kbdStruct->scanCode;

		BYTE lpKeyState[256];
		// Return is ignored, but it still does something.
		GetKeyboardState(lpKeyState);
		lpKeyState[Keys_hook::ShiftKey] = 0;
		lpKeyState[Keys_hook::Capital] = 0; 
		if (shift_active())
		{
			lpKeyState[Keys_hook::ShiftKey] = 0x80;
		}
		if (capital_active())
		{
			lpKeyState[Keys_hook::Capital] = 0x01;
		}

		char result;
		ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
		std::cout << result << std::endl;
	}

	KeepHookActive = false;

	if (KeepHookActive)
	{
		return CallNextHookEx(Handle_Hook, code, wParam, lParam);
	}
	else
	{
		UnhookWindowsHookEx(Handle_Hook);
		return NULL;
	}
	return CallNextHookEx(Handle_Hook, code, wParam, lParam);
}

void P::KeyListener::SetupHookLowLevel()
{
	Handle_Hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	if (Handle_Hook == NULL)
	{
		std::cout << "Keyboard hook failed!" << std::endl;
	}

	// This keeps the hook active.
	KeepHookActive = true;
	//while (GetMessage(NULL, NULL, NULL, NULL));
	//GetMessage(NULL, NULL, NULL, NULL);

	//std::thread GetMessageThread(GetMessageFunction);

	cout << "Continuing after SetupHookLowLevel GetMessage" << endl;
}

void GetMessageFunction()
{
	GetMessage(NULL, NULL, NULL, NULL);
}