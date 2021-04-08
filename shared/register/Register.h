#pragma once

/*
Contains functions to register a subsystem with the core server.
*/
namespace registration {

    /*
    Saves the arguments for future registration calls.

    nameLength should not include a null terminator.
    Unless attempting to connect to a different server, this function should only ever be called once.

    Returns false if the name length is too large.
    */
    bool initialize(const char* name, unsigned char nameLength);

    /*
    Attempts to connect to the registration pipe and register the client.

    If successful, received data is saved for future use.

    Returns the received status code, or -1 if the pipe was busy.
    */
    char request();

}