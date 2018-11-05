//main Function For The Crypted Document By Keylogger
//Function should take input file and output file names as args on startup

#include <iostream>
#include <string>
#include <fstream>
#include "Decrypt.h"

int main(int argc,char *argv[]) {

	if (argc != 3)
	{
		std::cout << "The Decrypt Funtion Needs 2 arguments \n";
		std::cout << " Input File And Output File " << std::endl, 2;
	}
	std::string input(argv[1]), output(argv[2]);

	std::ifstream finput (input);

	if (!finput)
	{
		return std::cout << "Cannot Read Input File :" << input << std::endl, 3;
	}
	std::string crypt_data;
	finput >> crypt_data;
	if (!finput)
	{
		return std::cout << "Input File :" << input <<"' corrupted'"<< std::endl, 4;
	}
	crypt_data = DecryptB64(crypt_data);
	std::ofstream foutput(output);
	if (!foutput)
	{
		return std::cout << "Cannot Write Output File :" << output << std::endl, 5;
	}
	foutput << crypt_data;
	if (!foutput)
	{
		return std::cout << "Output File :" << output << "' corrupted'" << std::endl, 6;
	}
	finput.close();
	foutput.close();
	return 0;

}
