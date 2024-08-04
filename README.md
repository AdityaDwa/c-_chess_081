# CHESS GAME

This project aims to develop a comprehensive and interactive chess game application using C++ and SFML, showcasing the principles of object-oriented programming (OOP). Chess is a classic and strategic board game which is an ideal project to demonstrate the power and flexibility of OOP.

## Table of Contents

- [Project Objectives](#project-objectives)
- [Features](#features)
- [Installation](#installation)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Contact](#contact)

## Project Objectives

- **Interactive and User-Intuitive** : Create a chess game that is engaging and easy to use.
- **Modular Design** : Utilize OOP principles to design the application in a modular, maintainable, and scalable way.
- **Fully Functional Chess Game** : Implement all official chess rules, including move validation, check detection and turn management.
- **Graphical User Interface** : Provide a user-friendly interface using SFML.

## Features

- **User-Friendly Interface** : Captivating visuals and an intuitive graphical interface make the game engaging and accessible for all players.
- **Educational Tools** : Features like possible moves generation and check indication help beginners learn the basics of chess.
- **Comprehensive Gameplay** : Supports all basic and special chess moves, including castling and pawn promotion, providing a competitive platform for intermediate to advanced players.

## Installation

1. **Clone the repository** :
    ```bash
    git clone https://github.com/AdityaDwa/c-_chess_081.git
    ```

2. **Install SFML** :
    Follow the instructions for your operating system from the [SFML website](https://www.sfml-dev.org/download.php).

3. **Build the project** :
    - Ensure SFML is correctly linked in your build system (e.g., Visual Studio, CMake, etc.).
    - Navigate to the directory containing the build.bat file and run the build script:
    ```bash
    .\build.bat
    ```

4. **Run the application** :
    - After the build is complete, navigate to the executable_files directory:
    ```bash
    cd .\executable_files\
    ```
    - Execute the compiled binary to start the application:
    ```bash
    .\Chess.exe
    ```

## Project Structure

```
c++_chess
├─ executable_files
│  └─ Chess.exe
├─ fonts
│  ├─ inter_bold.ttf
│  └─ inter_regular.ttf
├─ header_files
│  ├─ Button.h
│  ├─ Game.h
│  ├─ MatchState.h
│  └─ Piece.h
├─ source_file
│  ├─ Button.cpp
│  ├─ Game.cpp
│  ├─ main.cpp
│  ├─ MatchState.cpp
│  └─ Piece.cpp
├─ src
│  └─ image_files
├─ templates
│  └─ txt_files
├─ .gitignore
├─ build.bat
└─ README.md
```

- **main.cpp** : Entry point of the application and creates the game object.
- **Game.h / Game.cpp** : Handles game updating and rendering functions.
-  **MatchState.h / MatchState.cpp** : Contains all the game logic required during the chess match.
- **Piece.h / Piece.cpp** : Handles rendering of each piece object and their essential functions.
- **build.bat** : Batch file to compile the project.
- **executable_files** : Directory where the executable files will be placed after building the project.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## Contact

For any questions or suggestions, please contact me [here](mailto:adeetyadwa011@gmail.com).