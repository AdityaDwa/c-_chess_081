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

IF NOT EXIST logs (
    REM Command to create a folder
    mkdir logs
)


REM Command to compile the project
g++ -IC:\SFML-2.6.1\include -c "source_files/King.cpp" -o "object_files/King.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Queen.cpp" -o "object_files/Queen.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Rook.cpp" -o "object_files/Rook.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Knight.cpp" -o "object_files/Knight.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Bishop.cpp" -o "object_files/Bishop.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Pawn.cpp" -o "object_files/Pawn.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Piece.cpp" -o "object_files/Piece.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/MatchState.cpp" -o "object_files/MatchState.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/State.cpp" -o "object_files/State.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/Game.cpp" -o "object_files/Game.o"
g++ -IC:\SFML-2.6.1\include -c "source_files/main.cpp" -o "object_files/main.o"
g++ -LC:\SFML-2.6.1\lib "object_files\main.o" "object_files\Game.o" "object_files\State.o" "object_files\MatchState.o" "object_files/Piece.o" "object_files/Pawn.o" "object_files/Bishop.o" "object_files/Knight.o" "object_files/Rook.o" "object_files/Queen.o" "object_files/King.o" -o "executable_files\Chess.exe" -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

REM Check if the compilation was successful
IF %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
) ELSE (
    echo Compilation failed!
)