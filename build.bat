@echo off

REM Check if the folder exists
IF NOT EXIST executable_files (
    REM Command to create a folder
    mkdir executable_files
)

IF NOT EXIST object_files (
    REM Command to create a folder
    mkdir object_files
)



REM Command to compile the project
g++ -IC:\SFML-2.6.1\include -c "source_files/Entity.cpp" -o "object_files/Entity.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Button.cpp" -o "object_files/Button.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Game.cpp" -o "object_files/Game.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/GameState.cpp" -o "object_files/GameState.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/main.cpp" -o "object_files/main.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/MainMenuState.cpp" -o "object_files/MainMenuState.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/State.cpp" -o "object_files/State.o"
g++ -LC:\SFML-2.6.1\lib "object_files\main.o" "object_files\Game.o" "object_files\State.o" "object_files\GameState.o" "object_files\Entity.o" "object_files\MainMenuState.o" "object_files\Button.o" -o "executable_files\Chess.exe" -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

REM Check if the compilation was successful
IF %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
) ELSE (
    echo Compilation failed!
)
