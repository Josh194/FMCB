#include <iostream>

#include "minparse.h"

#include "Global.h"

int main(int argc, char** argv) {
	std::cout << "FMCB core server " << VERSION << std::endl;

	minparse::init(argc, argv);

	while (true) {
		minparse::argument arg = minparse::parse();

		if (arg.argc == -1) {
			break;
		}

		// Obviously not very good, minparse will need to be farther developed
		switch (arg.arg[0]) {
		case 't':
			if (arg.argc == 1) {
				std::cout << "Worker count set to " << arg.argv[0] << std::endl;
			}
			break;
		}
	}
}