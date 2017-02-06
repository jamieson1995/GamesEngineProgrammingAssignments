#include "Debug.h"
#include <Windows.h>

#include <string>
#include <iostream>

namespace jutiny
{

namespace engine
{

void Debug::Log(std::string _message)
{
	//Sets background colour to black, and text colour to white.
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
	std::cout << "Debug: " << _message << std::endl;
}

void Debug::LogWarning(std::string _message)
{
	//Sets background colour to yellow and text colour to blue.
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 225 );
	std::cout << "Warning: " << _message << std::endl;
	//Sets background colour to black, and text colour to white.
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
}

void Debug::LogError(std::string _message)
{
	//Sets background red to black, and text colour to white.
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 71 );
	 std::cout << "Error: " << _message << std::endl;
	 //Sets background colour to black, and text colour to white.
	 SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
}

}

}