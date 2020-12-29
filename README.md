# FMCB <!-- Logo replaces this line -->
![Release](https://img.shields.io/github/v/release/Josh194/FMCB)
![Version](https://img.shields.io/badge/dynamic/json?label=version&prefix=v&query=version&url=https%3A%2F%2Fraw.githubusercontent.com%2FJosh194%2FFMCB%2Fdevelop%2Finfo.json)
![Last Commit](https://img.shields.io/github/last-commit/Josh194/FMCB)
<!-- Add downloads badge later -->

FMCB is a cross-game platform that allows the linking of multiple games together.

Currently, we are only working on support for item linking in Factorio and Minecraft, but the project is fairly modular, and will eventually provide a robust API to allow linking any number of games together in any number of ways.

The project is organized into subsystems (the individual game mods) and the core server, which facilitates communication between the subsystems.

At the moment, this repository is home to the core server, and a Factorio and Minecraft subsystem respectively, but will eventually only host the core server; the subsystems will be relegated elsewhere, as our goal is provide a highly modular platform.

If you would like to build the project yourself, you will need CMake, Ninja, GCC, and Gradle, though Gradle is only needed to build the Minecraft subsystem, and will not be a requirement in the future. You can also build the repository with a different C/C++ compiler with some minor alterations to the CMake files.

If you would like to contribute, maybe wait a little while, as the project is in very early days, and general organization is still being worked on.

These docs are still in progress, and are very incomplete.
