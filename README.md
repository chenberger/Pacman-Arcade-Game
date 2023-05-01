
# The PAC-MAN Game

## Table of Contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Rules](#rules)
* [Run Locally](#run-locally)
* [Running Examples](#running-examples)

## General Info
Hey Guys,

Welcome to Pacman Game!

The main goal of this project is to implement the using of OOP with C++.

Me and my partner implemented the OOP principles, using classes, inheritence and polymorphism.

Also, I put my effforts on implementing "Strategy" design pattern.

Personally, it was my breakthrough in this project. Since then, adding objects and features became easier and practical.

Another nice thing to mention is that in order to instruct the ghosts to chase the Pac-Man (in professional diffculty level -> see down below in the rules), I've implemented BFS algorithem, that check in every single move what's the shortest possible path from the ghost to the Pac-Man.

For optimal game experience, set your console resolution to 25X80.

Note that the game could run in 4 modes:

1. Simple mode - running regular game via console UI.
2. Save mode - running the game with capturing all steps of the Pac-Man and Ghosts into a file.
3. Load mode - loading the last game that "Saved" in watching mode.
4. Load [Silent] mode - loading the last game that "Saved", but without any display to the user.

for 3,4 you'll get a message whether the "Test Passed" or not. (Menaning that the loaded game is same as the last that saved.)

Enjoy!

## Technologies
- C++ Programming language 
- Visual Studio 2019 on Windows 10

## Rules
The rules are short and simple.

The Pac-Man goal is to eat all the breadcrumbs, in order to finish a single board.

The boards will load one-by-one until losing or finishing all the boards.

*Note that you could choose the first board.

Only after completing all boards, the Pac-Man will be the winner.

Starting with 3 lives. each collision with the ghost will reduce the the lives by one.

"Special" breadcrumbs, (a number between 5 to 9) will appear sometimes on the board.
If the pacman eats this special breadcrumb it gets the points as the value of the digit (5 to 9).
*Note that eating a breadcrumb with the value of "9" (The max), will add lives to the Pac-Man by one.

In some boards, there are "Invisible-Tunnels". Namely, a tunnel that only the Pac-Man can go through. 

The game has 3 diffculty levels. Beginner, Amatuer, Professional.

In Beginner mode -> ghosts are moving randomally.

In Amatuer mode -> ghosts are half moving randomally, and half moving smart (chasing the Pac-Man)

In Professional mode -> ghosts are chasing the Pac-Man consistently.

Keys:

LEFT -> a or A

RIGHT -> d or D

UP -> w or W

Down -> x or X

STAY -> s or S

PAUSE GAME -> Esc


## Run Locally

Clone the project

```bash
  git clone https://github.com/AmirAnckonina/Pacman-Game.git
```

Go to the project directory

```bash
  cd Pacman
```

Run Solution ->
```bash
pacman_project.sln
```

Run Executable *Simple Mode* ->
```bash
pacman_project.exe
```

Run Executable  *Save Mode* ->
```bash
pacman_project.exe -save
```

Run Executable  *Load Mode* ->
```bash
pacman_project.exe -load
```

Run Executable  *Load [Silent] Mode* ->
```bash
pacman_project.exe -load -silent
```

## Running Examples


![App Screenshot](https://github.com/AmirAnckonina/Pacman/blob/35d51d7230a34d49800f350ce12864d5ec86eae5/Screenshots/Board.jpg)


![App Screenshot](https://github.com/AmirAnckonina/Pacman/blob/35d51d7230a34d49800f350ce12864d5ec86eae5/Screenshots/Board2.jpg)


![App Screenshot](https://github.com/AmirAnckonina/Pacman/blob/35d51d7230a34d49800f350ce12864d5ec86eae5/Screenshots/Board3.jpg)


![App Screenshot](https://github.com/AmirAnckonina/Pacman/blob/35d51d7230a34d49800f350ce12864d5ec86eae5/Screenshots/TinyBoard.jpg)
