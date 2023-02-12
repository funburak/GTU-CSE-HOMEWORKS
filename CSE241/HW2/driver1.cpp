#include <iostream>
#include <vector>

#include "tetris.hpp"
#include "tetromino.hpp"

using namespace std;

int main(){
    vector<Tetromino> tetro;
    tetro.push_back(Piece::I);
    tetro.push_back(Piece::O);
    tetro.push_back(Piece::T);
    tetro.push_back(Piece::J);
    tetro.push_back(Piece::L);
    tetro.push_back(Piece::S);
    tetro.push_back(Piece::Z);
    tetro.push_back(Piece::R);
    
    cout << "Creating a 25x25 tetris board" << endl;
    Tetris board(25,25);
    board.createBoard();
    board.Draw();
    board.Add(tetro[1].getShape());
    board.Animate(tetro[2].getShape());
    cout << "Added shape T to the board and animated it" << endl;

    cout << "Printing the tetrominos and 1 random at the end" << endl;
    for(int i=0; i<8; ++i){
        if(i == 7){
            cout << "The random tetromino" << endl;
            tetro[i].print();
        }
        else{
            tetro[i].print();
            cout << endl;
        }
    }
    cout << "Rotating tetrominos to left and printing" << endl;
    for(int i=0; i<8; ++i){
        if(i == 7){
            cout << "The random tetromino" << endl;
            tetro[i].rotate('l');
            tetro[i].print();
        }
        else{
            tetro[i].rotate('l');
            tetro[i].print();
            cout << endl;
        }
    }

    return 0;
}