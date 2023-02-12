#ifndef TETROMINO_H
#define TETROMINO_H

#include <iostream>

using namespace std;

namespace Tetrominos{

    enum class Piece{
    I='I',O='O',T='T',J='J',L='L',S='S',Z='Z',R='R'
    };

    class Tetromino{
        public:
            Tetromino();
            Tetromino(Piece piece);
            ~Tetromino(); // Destructor

            void print() const; // Prints the tetromino
            void rotate(char direction); // Rotates the tetromino with the given direction (left-right)
            int getRow() const; // Returns the row size of the shape
            int getCol() const; // Returns the column size of the shape
            char **getShape() const; // Returns the 2d shape array
            
            private:
                Piece piece_type;
                char **shape;
                int row;
                int col;
    };
} // end namespace

#endif // TETROMINO_H