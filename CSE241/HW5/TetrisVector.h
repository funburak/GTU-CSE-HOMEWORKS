#ifndef TETRISVECTOR_H
#define TETRISVECTOR_H

#include <iostream>
#include <vector>
#include <string>

#include "tetromino.h"
#include "AbstractTetris.h"

using namespace std;
using namespace tetros;
using namespace AbsTetris;

namespace VectTetris{

    class TetrisVector : public AbstractTetris{
        public:

            TetrisVector();
            TetrisVector(int row, int col);
        
            void createBoard();
            void draw() const override;
            void readFromFile(const string filename) override;
            void writeToFile(const string filename) override;
            void  operator+=(Tetromino &tetro) override;
            void animate(Tetromino &t,int move_c, char move_d, int rotate_c, char rotate_d) override;
            void deleteAdd(const Tetromino &t) override;
            void sleep()const  override;
            char lastMove() const override;
            int numberOfMoves() const override;
        
        private:
            vector<vector<char> > board;
            int board_row;
            int board_col;
            int total_move = 0;
    };
} // end namespace


#endif // TETRISVECTOR_H