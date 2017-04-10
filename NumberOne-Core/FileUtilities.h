//Not using this in favor of fstream
//fstream potentially slower but speed difference is irrelavent
//also this is old C code I don't really understand

#pragma once

#include <string>

namespace NumberOne {
		
	std::string	readFile(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");		//makes a file in stack, puts contents of filepath
		fseek(file, 0, SEEK_END);				//Finds end of file to make len char array
		unsigned long len = ftell(file);		//tells you what fileLen is, return unsigned long
		char* data = new char[len + 1];			//make char array for file contents
		memset(data, 0, len + 1);				//set each element in the array to 0, will leave garbage at end of string if not done
		fseek(file, 0, SEEK_SET);				//find beginning of file
		fread(data, 1, len, file);				//read the file, put contents in char array
		fclose(file);							//close file
		std::string out(data);					//make std string from char arrray with file contents
		delete[] data;							//delete char array
		return out;								//return string with file
	}
}

 // !FILE_UTILITES_H
