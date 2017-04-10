#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace NumberOne {

	const std::string loadFile(const char* filePath)
	{
		std::ifstream shaderFile;
		std::string sourceCode, line, temp;
		temp = filePath;

		shaderFile.exceptions(std::ifstream::badbit);
		try
		{
			shaderFile.open(filePath);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			sourceCode = shaderStream.str();
			shaderFile.close();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << ("Failed to open: " + temp) << std::endl;
		}

		if (sourceCode == "")
			std::cout << ("Failed to open: " + temp) << std::endl;

		return sourceCode;
	};
}
 // !FILE_READ_H
