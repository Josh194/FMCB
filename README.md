# FMCB <!-- Logo replaces this line -->
![Release](https://img.shields.io/github/v/release/Josh194/FMCB)
![Version](https://img.shields.io/badge/dynamic/json?label=version&prefix=v&query=version&url=https%3A%2F%2Fraw.githubusercontent.com%2FJosh194%2FFMCB%2Fdevelop%2Finfo.json)
![Platform](https://img.shields.io/badge/platform-win--32%20%7C%20win--64-lightgrey)
![Issues](https://img.shields.io/github/issues/Josh194/FMCB)
![Last Commit](https://img.shields.io/github/last-commit/Josh194/FMCB)
<!-- Add downloads badge later -->

FMCB is a platform that facilitates the linking of multiple applications together, with the goal being to shift the burden of managing complex networks from the client to the server.

Currently, we are only working on support for item linking in Factorio and Minecraft, but the project is fairly modular, and will eventually provide a robust API to allow linking any number of applications together in any number of ways.

The project is organized into subsystems (client applications that expose the functionality of some other system) and the core server, which manages communication between the subsystems.

At the moment, this repository is home to the core server, the client API, and an official Factorio and Minecraft subsystem. At some point after release 1.0.0, however, the subsystems will be moved elsewhere, as our goal is provide a highly modular platform.

If you would like to build the project yourself, you will need CMake, Ninja, GCC, and Gradle, though Gradle is only needed to build the Minecraft subsystem, and is not necessary. You could also potentially build the project with a different C/C++ compiler with some minor alterations to the CMake files.

At the moment, the project only supports windows, but this will be worked on in the future.

If you would like to contribute, maybe wait a little while, as the project is in very early days, and general organization is still being worked on, but otherwise, please read the CONTRIBUTING.md.

Some documentation exists on our github wiki, but it is still in progress, and is very incomplete.
