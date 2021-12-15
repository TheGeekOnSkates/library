#pragma once
#include <Windows.h>
#include <vector>

typedef void(*HotKeyCallback)();

/**
 * Super-thin object-oriented layer over the C functions that make up Win32 hotkeys
 */
class HotKey
{
public:

	/**
	 * Constructor - set up the hotkey
	 * @param[in] The hotkey's ID
	 * @param[in] Any modifier keys used (MOD_CONTROL, MOD_ALT etc.)
	 * @param[in] Any other keys used (VK_ESCAPE etc.)
	 * @param[in] Code to run when the hotkey is pressed (function 
	 *				pointer with no parameters or return value)
	 * @param[in] Handle the hotkey should apply to; if not used, the hotkey will be global
	 */
	HotKey(int id, int modifiers, int keys, HotKeyCallback callback, HWND handle = NULL)
	{
		this->handle = handle;
		this->id = id;
		this->mods = modifiers;
		this->keys = keys;
		this->callback = callback;
		RegisterHotKey(handle, id, modifiers, keys);
	}

	// Destructor: "Un-register" the hotkey
	~HotKey()
	{
		UnregisterHotKey(this->handle, this->id);
	}

	// Used by ProcessHotKeys
	int id;

	// Function pointer to run when hotkey is pressed
	HotKeyCallback callback;
private:
	// We don't need these YET, but we MIGHT down the road
	unsigned int mods;		// Modifier keys
	int keys;				// Keys
	HWND handle;			// HWND the hotkey is for
};

/**
 * Runs a message-listening loop for hotkeys
 * @param[in] A vector of HotKey instances
 */
void ProcessHotKeys(std::vector<HotKey> &keyz)
{
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		PeekMessage(&msg, NULL, 0, 0, 0);
		switch (msg.message)
		{
		case WM_HOTKEY:
			int length = keyz.size();
			for (int i = 0; i < length; i++)
			{
				if (msg.wParam == keyz[i].id)
				{
					keyz[i].callback();
				}
			}
		}
	}
}
