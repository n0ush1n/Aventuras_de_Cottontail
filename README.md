# Aventuras_de_Cottontail

YouTube link: https://www.youtube.com/watch?v=nAeEXjCtdUY&lc=UgxVWYLpOSX4VfLbpEt4AaABAg

To run the game in Ubuntu:

1) Make sure you have installed SDL2 libraries. If you have not, then open terminal and run the following commands :
    (i) sudo apt-get install g++
    (ii) sudo apt-get install libsdl2-2.0
    (iii) sudo apt-get install libsdl2-dev
    (iv) sudo apt-get install libsdl2-image-dev
    (v) sudo apt-get install libsdl2-mixer-dev
    (vi) sudo apt-get install libsdl2-ttf-dev
2) Now open terminal in the Game folder and run this command: make
3) Enjoy the game.

You can change the screen size of the game window in the code if you want to:
1) Go to the Game Folder. 
2) Go to the header folder.
3) Open defs.hpp.
4) Change the value of SCREEN_WIDTH & SCREEN_HEIGHT(just keep SCREEN_WIDTH:SCREEN_HEIGHT = 4:3).
