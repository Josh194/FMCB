#pragma once

#include <cstring>

namespace minparse {

	struct argument {
		/*
		A pointer to a character array representing the argument.
		
		Does not include the leading '-'.
		*/
		char* arg;

		/*
		The number of values provided to the argument.
		*/
		int argc;

		/*
		A pointer to the list of argument values.
		*/
		char** argv;
	};

	namespace {
		int index;
		int end_index;

		char** args;
	}

	/*
	Initializes the library with the given parameters, and sets the index to 0, unless the first parameter is not an argument, in which case the index will be set to the end of the parameter list.
	*/
	void init(int argc, char** argv) {
		end_index = argc;
		args = argv;

		if (argv[0][0] == '-') { // argv must start with an actual argument
			index = 0;
		} else {
			index = end_index;
		}
	}

	/*
	Stores the next argument in arg_p.

	Returns false if there is nothing left to parse.
	*/
	inline bool parse(argument* arg_p) {
		int current_arg = index; // Remember the argument we are currently parsing

		while (index++ < end_index) { // Check if we are still in bounds
			if (index == end_index || args[index][0] == '-') { // Would be slightly faster to reverse the order of the OR, but this works fine
				arg_p -> arg = args[current_arg] + 1; // Add 1 to the pointer to disregard the leading '-'
				arg_p -> argc = index - 1 - current_arg; // Index is at the next argument, so subtract 1 to get the last value instead
				arg_p -> argv = args + current_arg + 1; // Add 1 so as to not include the argument itself

				return true;
			}
		}

		return false;
	}

}