# Bounce Ball

## Introduction

**Full name:** Bùi Minh Hoạt

**Student ID:** 21020326

**University:** VNU University of Engineering and Technology (VNU-UET)

**Mail for work:** official.buiminhhoat@gmail.com

**Video demo:** https://youtu.be/K7zEpGcd7gw

## Technologies

**Project uses:**

- Microsoft Visual Studio 2022.
- SDL2 devel 2.0.20 mingw.
- SDL2 image devel 2.0.5 mingw.
- SDL2 ttf devel 2.0.18 mingw.
- SDL2 mixer devel 2.0.4 mingw.

## How to compile and play

- **Windows 64bit**: 
    - Clone this repository to your computer.
        - **Way 1:**
            - Requirements: Microsoft Visual Studio.
            - Open file **Bounce-Ball.sln**.
            - Run.
        - **Way 2:**
            - Open **x64/ Debug/ Bounce-Ball.exe**.

## Contents

### How to play

You have to control the ball to the finish line, avoiding the obstacle on the way. If the ball touch the obstacle, it will pop and you will lose **ONE** life. **GAMEOVER** when you run out of lives.

After being granted an account, you can play game right away. Initially, your level is level $1$ out of $50$ levels. You can only unlock the next level when you complete the current level.

### Main function:
- Optimize CPU and RAM. CPU does not run more than 10%, RAM does not exceed 50 MB.
- Game database security encryption system.
- Login/account registration, and password when playing games. The highscore will be automatically updated to the leaderboard.
- Sound setting.


### Controls:

- **LEFT arrow key**  :       Move left.
- **RIGHT arrow key** :       Move right.
- **SPACE key**       :       Move up.

## Algorithm
- **Map**: I divided the game map into many smaller maps of $8 * 28$ size and use my algorithm to combine the minimaps into the complete map in the game.
