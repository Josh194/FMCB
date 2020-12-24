start /wait cmd /c "gradlew build"
del "run\mods\*.jar"
xcopy build\libs run\mods
del "build\libs\*.jar"
pause