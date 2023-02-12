#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <iostream>
#include <vector>

using namespace std;

enum class Piece{
    I='I',O='O',T='T',J='J',L='L',S='S',Z='Z',R='R'
};

class Tetromino{
    public:
        // Constructors
        Tetromino();
        Tetromino(Piece piece);

        void print() const; // Prints the tetromino shape
        void rotate(char direction); // Rotates the tetromino shape left or right
        vector<vector<char> > getShape(); // Getter of the shape        

    private:
        vector<vector<char> > shape;
        Piece piece_type;

};

#endif // TETROMINO_HPP