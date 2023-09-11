# TicTacToe

A simple console version of the tic-tac-toe game with the minmax algorithm.

## General Information

The Minimax algorithm is a decision-making algorithm commonly used in two-player, zero-sum games such as chess or tic-tac-toe. It aims to find the optimal move for a player by considering all possible future moves and their outcomes, assuming that the opponent also plays optimally. The algorithm alternates between maximizing the player's score and minimizing the opponent's score, ultimately leading to a strategy that maximizes the player's chances of winning or minimizing the chances of losing.


## Instalation

To install, you must have CMake and gcc.

Fedora:

```bash
sudo dnf install gcc
sudo dnf install cmake
```
Debian:
```bash
sudo apt get install gcc
sudo apt get install cmake
```


## Build and run project

To build this project you just need to run the script.

```bash
sh build.sh
```

And to start.

```bash
sh run.sh
```

## Game Overview

To enter coordinates, enter the digit indicating the x coordinate, followed by the space y.


```bash
                    _____ _     _____         _____                   
                   |_   _(_) __|_   _|_ _  __|_   _|__   ___          
                     | | | |/ __|| |/ _` |/ __|| |/ _ \ / _ \       
                     | | | | (__ | | (_| | (__ | | (_) |  __/         
                     |_| |_|\___||_|\__,_|\___||_|\___/ \___|    



                                       O |   |   
                                      ---|---|---
                                         |   |   
                                      ---|---|---
                                         |   |   


Podaj wspolrzedne:


```

