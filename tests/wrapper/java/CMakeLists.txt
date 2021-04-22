# Clean this up
find_package(Java 1.8 REQUIRED) # How should we handle Java versions?
include(UseJava)

add_jar(Test_JavaWrapper
    Run.java
    INCLUDE_JARS JavaWrapper
    ENTRY_POINT Run)