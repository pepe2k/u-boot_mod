/* A couple of exceptions for lzmp.
 *
 * Copyright (C) 2005 Ville Koskinen
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
using std::string;

class Exception
{
private:
	string message;
public:
	Exception(char *what): message(what) { }
	Exception(string what): message(what) { }

	~Exception() { }

	string what(void) { return message; }
};

class ArgumentException: public Exception
{
public:
	ArgumentException(char *what): Exception(what) { }
	ArgumentException(string what): Exception(what) { }

	~ArgumentException() { }
};

#endif

