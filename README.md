# 2048

### A console-based version of the classic 2048 game written in C.  

## Instructions
#### To run the game, open the 2048.exe application.
To play 2048, you will need to press the keys (that you can change),
w, s, a, and d, to move the tiles around. Tiles will move in the
direction you enter, and if they hit another tile of the same value, the
tiles will merge together and their value will double.

For every move that is made, an additional value, either 2 (90% of the time) or 4 (10% of the time), will
be added to a random location.

Score is kept by adding the value of tiles that are created from merges.

The game will end if no more moves can be made or 0 is entered at any time.

## Files
- **2048.exe** - compiled Windows executable
- **2048.c** - main source code  
- **2048_support.h** - helper functions and console utilities  

#### If desired, the game can be compiled directly from the '.c' and '.h' source files using a compiler such as VSC or Code::Blocks.
Ensure you have installed MinGW before compiling. MinGW can be downloaded here:
https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/

You can also compile directly from the Command Prompt or Powershell:
```
   gcc 2048.c -o 2048.exe
   2048.exe
```
## Cloning the Repository
To clone this repository:
```
cd C:\Users\[Username]\Desktop [Or other desired local address to clone repository]
git clone https://github.com/TwistedCorner04/2048.git
cd 2048
```

## License
This project is licensed under the MIT License. See `LICENSE` for details.
