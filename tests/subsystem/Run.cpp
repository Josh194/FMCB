#include <iostream>

#include "Register.h"
#include "BufferAccess.h"

// ! TODO: use wrapper (do we need a C++ wrapper?)
int main() {
    std::cout << "Attempting to connect to core server" << std::endl;

    // ! Isn't used by request() yet
    // registration::initialize();

    if (registration::request() == 0) {
        std::cout << "Connection successful" << std::endl;

        std::cout << communication::map() << std::endl;
        std::cout << +communication::unmap() << std::endl;
    } else {
        std::cout << "Connection failed" << std::endl;
    }

    return 0;
}