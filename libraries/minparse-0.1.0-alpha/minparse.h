#pragma once

#include <cstring>

namespace minparse {

	struct argument {
		char* arg;

		int argc;
		char** argv;
	};

	namespace {
		int arg_cpy;

		int argc_cpy;
		char** argv_cpy;
	}

	void init(int argc, char** argv) {
		argc_cpy = argc - 1;
		argv_cpy = argv;

		arg_cpy = 0;
	}

	inline argument parse() {
		int arg_current = arg_cpy;

		while (true) {
			if (arg_cpy == argc_cpy + 1) {
				return {
					nullptr,
					-1,
					nullptr
				};
			}

			// Order could be a bit faster
			if (arg_cpy++ == argc_cpy || argv_cpy[arg_cpy][0] == '-') {
				return {
					argv_cpy[arg_current] + 1,
					arg_cpy - 1 - arg_current,
					argv_cpy + arg_current + 1
				};
			}
		}
	}

}