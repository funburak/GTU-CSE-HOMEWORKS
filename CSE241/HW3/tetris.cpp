#include <iostream>
#include <chrono>
#include <thread>

#include "tetromino.h"
#include "tetris.h"

using namespace std;
using namespace Tetrominos;

namespace TETRIS{

    Tetris::Tetris(){ // No parameter constructor makes a non-usable board
        board_row = 0;
        board_col = 0;
    }

    Tetris::Tetris(int row, int col){ 
        board_row = row + 2;
        board_col = col + 2;

        Board = new char*[board_row];
        for(int i=0; i<board_row; ++i){
            Board[i] = new char[board_row];
        }
        for(int r=0; r<board_row; ++r){
            for(int c=0; c<board_col; ++c){
                if(r == 0 || r == board_row-1 || c == 0 || c == board_col -1){
                    Board[r][c] = '#';
                }
                else{
                    Board[r][c] = ' ';
                }
            }
        }

    }

    Tetris::~Tetris(){ // Destructor
        for(int i=0; i<board_row; ++i){
            delete[] Board[i];
        }
        delete[] Board;
        Board = nullptr;
    }

    void Tetris::Draw() const{ // Prints out the board
        for(int r=0; r<board_row; ++r){
            for(int c=0; c<board_col; ++c){
                cout << Board[r][c];
            }
            cout << endl;
        }
    }

    void Tetris::operator+=(const Tetromino& t){ // Adds tetromino to the top row at mid
        char ** shape = t.getShape();
        int mid_col = board_col / 2;
        for(int r=0; r<t.getRow(); ++r){
            for(int c=0; c<t.getCol(); ++c){
                Board[r+1][mid_col + c - 1] = shape[r][c];
            }
        }
    }

    void Tetris::DeleteAdd(const Tetromino& t){ // Deletes the added tetromino from the top row at mid
        for(int r=0; r<t.getRow(); ++r){
            for(int c=0; c<t.getCol(); ++c){
                Board[r+1][board_col/2 + c - 1] = ' ';
            }
        }
    }

    void Tetris::Animate(Tetromino &t,char move_d, int move_c,char rotate,int rot_c){
        int count = 0;
        int bottom = board_row - 1;
        for(int i=0; i<rot_c; ++i){ // Rotate the shape of the tetromino rotation count times
            t.rotate(rotate);
        }
        char **shape = t.getShape();
        cout << "Shape of tetromino:" << endl;
        t.print();
        if(move_d == 'l'){ // If the given move direction is to the left make move count minus.
            move_c *=-1;
        }
        while(count <= bottom){
            this->Draw();
            this->DeleteAdd(t);
            if(move_d == 'r'){ // If the move direction is to the right and out of border of the board
                if(move_c + board_col / 2 > board_col-2){
                    cout << "You have exceed the boards border" << endl;
                    break;
                }
            }
            else if(move_d == 'l'){ // If the move direction is to the left and out of border of the board
                if(board_col / 2 + move_c < 2){
                    cout << "You have exceed the boards border" << endl;
                    break;
                }
            }
            
            

            for(int i=1; i<t.getCol()+1; ++i){ // Collision check
                if(Board[i+count+t.getCol()][board_col/2+move_c+i] != ' '){
                    return;
                }
            }

            for(int r=0; r<t.getRow(); ++r){ // Erases the previous point
                for(int c=0; c<t.getCol(); ++c){
                    Board[count+1+r][board_col/2+move_c+c-1] = ' ';
                }
            }
            for(int r=0; r<t.getRow(); ++r){ // Puts the shape on the board
                for(int c=0; c<t.getCol(); ++c){
                    Board[count+2+r][board_col/2+move_c+c-1] = shape[r][c];
                }
            }
            this->Sleep();
            count++;
            if(t.getRow() + count >=bottom-1){
                break;
            }
        }
        this->Draw();
    }

    void Tetris::Sleep() const{
        this_thread::sleep_for(chrono::milliseconds(50)); // Sleeps 50 miliseconds
        cout << "\x1b[2J"; // Erases entire screen
        cout << "\x1b[H"; // Move cursor to home position (0,0)
    }




} // end namespace