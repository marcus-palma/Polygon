// This file is only for listening for keyboard input.

#pragma once

#include <vector>
#include <Windows.h> // Keyboard input.

namespace P {
	class KeyListener;
}

class P::KeyListener {
public:
	// Listen for keys getting pressed. Returns >0 for a Virtual Key number. Returns -1 on fail.
	int ListenForKeys(std::vector<int>* Keys);

	void SetupHookLowLevel();

	// Returns VirtualKey integer.
	int KeyListenerLoop();
	
	// Windows high level keyboard input stuff.
	HANDLE hStdin = NULL;
	DWORD fdwSaveOldMode = 0;
	void Keyboard_HighLevelRead();
	void ErrorExit(LPCSTR);
	void KeyEventProc(KEY_EVENT_RECORD);
	void MouseEventProc(MOUSE_EVENT_RECORD);
	void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

private:
	bool KeyIsFound = false;

	// The reference to the keys to listen for is stored here.
	std::vector<int>* Keys; // = NULL;

	int FoundKey = 0;
};

void GetMessageFunction();