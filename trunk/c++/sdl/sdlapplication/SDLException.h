#ifndef SDLEXCEPTION_H
#define SDLEXCEPTION_H

#include <stdexcept>
#include <string>
#include <SDL.h>

class SDLException : public std::runtime_error
{
private:
	static const std::string prefix;
public:
	SDLException()
		: std::runtime_error(prefix + SDL_GetError())
	{
	};

	SDLException(const std::string& message)
		: std::runtime_error(prefix + message)
	{
	};
};

inline void SDLCheck(int code)
{
	if(code < 0)
		throw new SDLException();
}

class NotImplementedException : public std::runtime_error
{
public:
	NotImplementedException()
		: std::runtime_error("Not implemented yet.")
	{
	};

	NotImplementedException(const std::string& message)
		: std::runtime_error("Not implemented yet: " + message)
	{
	};
};

class AssertionException : public std::runtime_error
{
public:
	AssertionException(const std::string& message)
		: std::runtime_error("Assert failed: " + message)
	{
	};
};

#endif
