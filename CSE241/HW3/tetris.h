#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>

#include "tetromino.h"

using namespace std;
using namespace Tetrominos;

namespace TETRIS{

    class Tetris{
        public:
            Tetris();
            Tetris(int row, int col);
            ~Tetris(); // Destructor

            void Draw() const; // Prints the tetris board
            void operator+=(const Tetromino& t); // Adds tetromino at the middle of the board
            void DeleteAdd(const Tetromino &t); // Deletes the added tetromnio at the middle
            void Animate(Tetromino &t, char move_d, int move_c, char rotation, int rot_c); // Drops the tetromino by 1 index until it hits the bottom or collide with other tetromino
            void Sleep() const; // Erases the screen and waits for 50 miliseconds
            int getRow() const {return board_row;};
            int getCol() const {return board_col;};

        private:
            char **Board;
            int board_row;
            int board_col;
    };
} // end namespace

#endif // TETRIS_H