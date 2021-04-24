#include <iostream>

#include "LinkedArray.h"

int main() {
    LinkedArray<int, 20> la = LinkedArray<int, 20>();

    std::cout << "test" << std::endl;

    for (int i = 0; i < 10; i++) {
        *la.add() = i;
    }

    la.deleteNext(la.getHead());
    la.deleteNext(la.getHead() -> next);

    for (int i = 10; i < 12; i++) {
        *la.add() = i;
    }

    return 0;
}