#include <iostream>

#include <Windows.h>

int main() {
    std::cout << "Attempting to connect to core server" << std::endl;

    CallNamedPipeA(
        "FMCBCoreConnect",
         


    );

    return 0;
}