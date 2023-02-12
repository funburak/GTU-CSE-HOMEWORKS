#include <iostream>

#include "tetromino.h"
#include "tetris.h"

using namespace std;

using namespace Tetrominos;
using namespace TETRIS;

int main(){
    Tetromino t1(Piece::T);
    Tetromino t2(Piece::J);
    Tetromino t3(Piece::O);

    Tetris board(20,20);
    board+=t1;
    board.Draw();
    board.Animate(t1,'r',5,'l',1);
    board+=t2;
    board.Draw();
    board.Animate(t2,'r',3,'l',1);
    board+=t3;
    board.Draw();
    board.Animate(t3,'r',3,'l',0);
    cout << "Rotated shape T 1 time to the left" << endl;
    cout << "Rotated shape J 1 time to the left" << endl;
    cout << "Don't need to rotate shape O" << endl;
    cout << "Added all the tetromino shapes to the board and animated it." << endl;
    return 0;
}