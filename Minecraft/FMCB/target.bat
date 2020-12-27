@rem This file builds the core MC subsystem, and is run automatically via a CMake target

@start cmd.exe /k gradlew build

@rem Later, add functionality to copy files to correct directories, etc (could maybe be done by CMake?)