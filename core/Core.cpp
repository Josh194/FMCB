#include <iostream>

#include "minparse.h"

#include "Global.h"

int main(int argc, char** argv) {
	std::cout << "FMCB core server " << VERSION << std::endl;

	minparse::init(argc - 1, argv + 1);

	minparse::argument arg = {};

	while (minparse::parse(&arg)) {
		// Obviously not very good, minparse will need to be farther developed
		switch (arg.arg[0]) {
		case 't':
			if (arg.argc == 1) {
				std::cout << "Worker count set to " << arg.argv[0] << std::endl;
			}

			break;
		case 's':
			if (arg.argc == 1) {
				std::cout << "Max subsystems set to " << arg.argv[0] << std::endl;
			}

			break;
		}
	}
}