#ifndef JUTINY_ENGINE_DEBUG_H
#define JUTINY_ENGINE_DEBUG_H

#include <string>

namespace jutiny
{

namespace engine
{

class Debug
{
public:

	//Prints white text on a black background with specifed message to the console.
	static void Log(std::string _message);

	//Prints blue text on a yellow background with specified message to the console.
	static void LogWarning(std::string _message);

	//Prints white text on a red background with specified message to the console.
	static void LogError(std::string _message);

};

}

}

#endif

