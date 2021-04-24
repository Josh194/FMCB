#include "Translate.h"

#include <cstring>

void* tmpPtr; // ! TODO: REMOVE
char tmp[512]; // ! TODO: REMOVE

// Client count is already checked in CScheduler for now
void translate::process(void* communication, unsigned int clientIndex, unsigned int clientCount) {
    if (clientIndex == 1) { // ! TODO: don't hardcode
        std::memcpy(tmpPtr + 512, communication, 512);
        std::memcpy(communication + 512, tmp, 512);
    } else {
        tmpPtr = communication;

        std::memcpy(tmp, communication, 512);
    }
}