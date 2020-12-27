# Consider adding BYPRODUCTS later so that ninja can automatically detect missing files (does SOURCES affect anything?)
# USES_TERMINAL allows gradle to build in parallel, and to place it's output into the terminal. Unfortunately, ninja is a bit buggy, and will not buffer correctly, resulting in only the last command in the other pool displaying.
add_custom_target(Minecraft ALL target.bat
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/FMCB
	USES_TERMINAL)