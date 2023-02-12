#ifndef TETROMINO_H
#define TETROMINO_H

#include <iostream>
#include <vector>

using namespace std;

namespace tetros{
    enum class Piece{
        I='I',O='O',T='T',J='J',L='L',S='S',Z='Z',R='R'
    };

    class Tetromino{
        public:
            Tetromino();
            Tetromino(Piece p);
            void print() const;
            void rotate(char direction);
            vector<vector<char> > getShape();
            int getRow() const;
            int getCol() const;

        private:
            vector<vector<char> > shape;
            Piece piece_type;
    };

} // end namespace

#endif // TETROMINO_H