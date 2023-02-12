#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

#include "tetromino.h"
#include "AbstractTetris.h"
#include "Tetris1D.h"

using namespace std;
using namespace tetros;
using namespace AbsTetris;

namespace Tetris1D{

    TetrisArray1D::TetrisArray1D(){
        board_row = 1;
        board_col = 1;
        board_size = board_row * board_col;
        board = new char[board_size];
    }

    TetrisArray1D::TetrisArray1D(int row, int col){
        board_row = row;
        board_col = col;
        board_size = board_row * board_col;
        board = new char[board_size];
    }

    TetrisArray1D::~TetrisArray1D(){
        delete [] board;
        board = nullptr;
    }

    void TetrisArray1D::createBoard(){
        delete [] board;

        char *temp = new char[board_size];
        for(int i=0; i<board_size; ++i){
            temp[i] = ' ';
        }

        for (int r = 0; r < board_row; ++r) {
            for (int c = 0; c < board_col; ++c) {
                if (r == 0 || r == board_row - 1 || c == 0 || c == board_col - 1) {
                    temp[r * board_col + c] = '#';
                }            
            }
        }
        board = temp;
    }


    void TetrisArray1D::draw()const{
        for(int r=0; r<board_row; ++r){
            for(int c=0; c<board_col; ++c){
                cout << board[r*board_col + c];
            }
            cout << endl;
        }
    }

    void TetrisArray1D::readFromFile(string filename){
        vector<vector<char>> vect;

        ifstream read;
        read.open(filename);
        
        string line;
        while(getline(read,line)){
            vector<char> temp;
            for(char c: line){
                temp.push_back(c);
            }
            vect.push_back(temp);
        }

        read.close(); // Close file
    }

    void TetrisArray1D::writeToFile(string filename){
        ofstream write;
        write.open(filename,std::ios::out);

        for(int r=0; r<board_row; ++r){
            for(int c=0;c<board_col; ++c){
                int index = r*board_col + c;
                write << board[index];
            }
            write << endl;
        }
        write.close();
    }

    void TetrisArray1D::operator+=(Tetromino &t){
        vector<vector<char> > shape = t.getShape();
        int mid_col = board_col / 2;
        for(int r=0; r<shape.size(); ++r){
            for(int c=0; c<shape[0].size(); ++c){
                board[(r+1)*mid_col+c-1] = shape[r][c];
            }
        }
    }

    void TetrisArray1D::deleteAdd(const Tetromino &t){
        for(int r=0; r<t.getRow(); ++r){
            for(int c=0; c<t.getCol(); ++c){
                board[(r+1)*board_col/2+c-1] = ' ';
            }
        }
    }

    void TetrisArray1D::animate(Tetromino &t,int move_c, char move_d, int rotate_c, char rotate_d){
        int count = 0;
        int bottom = board_row - 1;

        for(int i=0; i<rotate_c; ++i){
            t.rotate(rotate_d);
        }

        vector<vector<char> > shape = t.getShape();
        cout << "Shape of the tetromino." << endl;
        t.print();

        if(move_d == 'l'){
            move_c *= -1;
        }

        while(count <= bottom){
            this->draw();
            this->deleteAdd(t);

            if(move_d == 'r'){
                if(move_c + board_col/2 > board_col -2){
                    cerr << "You have exceeded the boards border." << endl;
                    break;
                }
            }

            else if(move_d == 'l'){
                if(move_c + board_col/2 < 2){
                    cerr << "You have exceeded the boards border." << endl;
                    break;
                }
            }

            for(int i=1; i<t.getCol()+1; ++i){ // Collision check
                if(board[(i + count + t.getCol()) * board_col + board_col / 2 + move_c + i] != ' '){
                    return;
                }
            }

            for(int r=0; r<shape.size(); ++r){ // Erases the previous point
                for(int c=0; c<shape[0].size(); ++c){
                    board[(r+count+1)* board_col + board_col/2+move_c+c-1] = ' ';
                }
            }

            for(int r=0; r<shape.size(); ++r){ // Puts the tetromino to the board
                for(int c=0; c<shape[0].size(); ++c){
                    board[(r+count+2)*board_col+board_col/2+move_c+c-1] = shape[r][c];
                }
            }

            this->sleep();
            count++;
            moves++;            
            if(shape.size() + count >= bottom){
                break;
            }
        }
        this->draw();
    }

    void TetrisArray1D::sleep() const{
        this_thread::sleep_for(chrono::milliseconds(50)); // Sleeps 50 miliseconds
        cout << "\x1b[2J"; // Erases entire screen
        cout << "\x1b[H"; // Move cursor to home position (0,0)
    }

    char TetrisArray1D::lastMove()const{
        return 'd';
    }

    int TetrisArray1D::numberOfMoves()const{
        return moves;
    }

} // end namespace
