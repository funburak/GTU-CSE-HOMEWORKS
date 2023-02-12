#ifndef TETROMINOS_H
#define TETROMINOS_H

#include <iostream>
#include <vector>

using namespace std;

enum class Piece{
    I='I',O='O',T='T',J='J',L='L',S='S',Z='Z'
};

class Tetromino{
    public:
        Tetromino(); // Empty constructor
        Tetromino(Piece piece); // Construct object with the entered piece type and an empty shape vector
        
        void rotate(char direction);
        void print() const;
        bool canFit(const Tetromino &other, char position) const;
        void createShape(); // Creates the shape of the tetromino with its identical character in 2d vector
        void createBoard(); 

    private:
        Piece piece_type;
        vector<vector<char> > shape; // 2d 4x4 character array for tetromino shapes


};



#endif // TETROMINOS_H