// Has the functions and configurations for Encoding/Encrypting
#ifndef BASE_64_H
#define BASE_64_H

#include <vector>
#include <string>

namespace Base64
{

	std::string Base64_encode(const std::string &);
//SALT's are for increasing the strenght of our Encrypting
	const std::string &SALT1 = "LM::TB::BB";
	const std::string &SALT2 = "_:/_77";
	const std::string &SALT3 = "line=wowC++";

//Encrypting the File with adding SALTS
	std::string Encrypt64(std::string str)
	{
		str = SALT1 + str + SALT2 +  SALT3;
		str = Base64_encode(str);
		str.insert(7, SALT3);
		str += SALT1;
		str = Base64_encode(str);
		str += SALT2 + SALT3 + SALT1;
		str = Base64_encode(str);
		str.insert(1, "L");
		str.insert(7, "M");
		return str;
	}
//Base64 Keys implemented here
	const std::string &Base64_Keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	
//Encoding Done here by left-shifting characters 6 bits
	std::string Base64_encode(const std::string &str)
	{
		std::string returnString;
		int val = 0; // index we use to map input to our table
		int bits = -6; // be used to number of bits
		const unsigned int b63=0x3F;

		for (const auto &ch : str)
		{
			val = (val << 8) + ch;
			bits += 8;
			while (bits >= 0)
			{
				returnString.push_back(Base64_Keys[(val >> bits) & b63]);
				bits -= 6;
			}
		}
		if (bits > -6)
		{			
			returnString.push_back(Base64_Keys[((val << 8) >>(bits+8)) & b63]);
		}
		while (returnString.size() % 4)
		{
			returnString.push_back('-');
		}
		return returnString;
	}
}

#endif

