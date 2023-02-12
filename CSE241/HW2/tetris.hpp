#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <iostream>
#include <vector>

using namespace std;

class Tetris{
    public:
        // Constructors
        Tetris();
        Tetris(int row, int col);

        void createBoard(); // Creates a board with '#' characters at the border and empty characters inside
        void Draw() const; // Prints out the board
        void Add(vector<vector<char> > tetro); // Adds tetromino to the mid at the top of the board
        void DeleteAdd(vector<vector<char> > tetro); // Deletes the added tetromino to the top
        void Animate(vector<vector<char> > tetro); // First finds the empty position from the bottom and then animates tetromino down
        void Sleep(); // Clears the terminal and set the cursor to (0,0) position and sleeps for 50 miliseconds
        bool Fit();
        

    private:
        vector<vector<char> > Board;
        int board_row;
        int board_col;    
};

#endif // TETRIS_HPP