#ifndef TETRIS1D_H
#define TETRIS1D_H

#include <iostream>
#include <string>

#include "tetromino.h"
#include "AbstractTetris.h"

using namespace std;
using namespace tetros;
using namespace AbsTetris;

namespace Tetris1D{

    class TetrisArray1D : public AbstractTetris{
        public:
            TetrisArray1D();
            TetrisArray1D(int row, int col);
            ~TetrisArray1D(); // Destructor

            void createBoard();
            void draw()const override;
            void readFromFile(const string filename) override;
            void writeToFile(const string filename) override;
            void operator+=(Tetromino &tetro) override;
            void deleteAdd(const Tetromino &other)override;
            void animate(Tetromino &t,int move_c, char move_d, int rotate_c, char rotate_d) override;
            void sleep() const override;
            char lastMove() const override;
            int numberOfMoves() const override;

        private:
            char *board;
            int board_row;
            int board_col;
            int board_size;
            int moves = 0;

    };

} // end namespace

#endif // TETRIS1D_H


