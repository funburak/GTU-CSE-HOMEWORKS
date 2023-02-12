#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "AbstractTetris.h"
#include "tetromino.h"
#include "TetrisVector.h"

using namespace std;
using namespace tetros;
using namespace AbsTetris;

namespace VectTetris{

    TetrisVector::TetrisVector(){
        board_row = 0;
        board_col = 0;
    }

    TetrisVector::TetrisVector(int r, int c){
        board_row = r+2;
        board_col = c+2;
    }
    
    // Makes a board with dimension rowXcol and makes the boards #.
    void TetrisVector::createBoard(){
        vector<vector<char> > Temp(board_row,vector<char>(board_col,' '));
        for(int r=0; r<board_row; ++r){
            for(int c=0; c<board_col; ++c){
                if(r == 0 || r == board_row-1 || c == 0 || c == board_col-1){
                    Temp[r][c] = '#';
                }            
            }
        }
        board = Temp;
    }

    // Prints the board
    void TetrisVector::draw() const{
        for(int r=0; r<board_row; ++r){
            for(int c=0; c<board_col; ++c){
                cout << board[r][c];
            }
            cout << endl;
        }
    }
    
    // This function reads the game from the game.txt file, writes it to a 2D char vector and prints it.
    void TetrisVector::readFromFile(const string filename){
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

        cout << "Printing the text file!" << endl;
        for(int r=0; r<vect.size(); ++r){
            for(int c=0; c<vect[0].size(); ++c){
                cout << vect[r][c];
            }
            cout << endl;
        }
    }

    // This function writes the board to the game.txt file.
    void TetrisVector::writeToFile(const string filename){
        ofstream write;
        write.open(filename,std::ios::out);

        for(auto &row: board){
            for(auto &i: row){
                write << i;
            }
            write << endl;
        }
        write.close();
    }

    // Adds tetromino to the middle of the top row
    void TetrisVector::operator+=(Tetromino &other){
        vector<vector<char>> temp = other.getShape();
        int mid_col = board_col / 2;
        for(int r=0; r<other.getRow(); ++r){
            for(int c=0; c<other.getCol(); ++c){
                board[r+1][mid_col+c-1] = temp[r][c];
            }
        }
    }

    // Deletes the added tetromino to the middle of the top row
    void TetrisVector::deleteAdd(const Tetromino &t){
        for(int r=0; r<t.getRow(); ++r){
            for(int c=0; c<t.getCol(); ++c){
                board[r+1][board_col/2 + c - 1] = ' ';
            }
        }
    }

    // Animates the tetromino piece in the board until it hits bottom or collides with another tetromino piece
    void TetrisVector::animate(Tetromino &t,int move_c, char move_d, int rotate_c, char rotate_d){
        int count = 0;
        int bottom = board_row - 1;
        for(int i=0; i<rotate_c; ++i){
            total_move++;
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
                if(move_c + board_col / 2 > board_col - 2){
                    cout << "You have exceeded the boards border." << endl;
                    break;
                }
            }

            else if(move_d == 'l'){
                if(board_col / 2 + move_c < 2){
                    cout << "You have exceeded the boards border." << endl;
                    break;
                }
            }

            for(int i=1; i<t.getCol()+1; ++i){ // Collision check
                if(board[i+count+t.getCol()][board_col/2+move_c+i] != ' '){
                    return;
                }
            }

            for(int r=0; r<shape.size(); ++r){ // Erases the previous point
                for(int c=0; c<shape[0].size(); ++c){
                    board[r+count+1][board_col/2 + move_c +c-1] = ' ';
                }
            }

            for(int r=0; r<shape.size(); ++r){ // Puts shape to the board
                for(int c=0; c<shape[0].size(); ++c){
                    board[r+count+2][board_col/2 + move_c + c-1] = shape[r][c];
                }
            }

            this->sleep();
            count++;
            total_move++;
            if(shape.size() + count >= bottom-1){
                break;
            }
        }
        this->draw();
    }

    // Sleeps for 50ms and erases the screen.
    void TetrisVector::sleep()const{
        this_thread::sleep_for(chrono::milliseconds(50)); // Sleeps 50 miliseconds
        cout << "\x1b[2J"; // Erases entire screen
        cout << "\x1b[H"; // Move cursor to home position (0,0)
    }

    char TetrisVector::lastMove() const{
        return 'd';
    }

    // Returns the number of moves the board has made including rotation of the tetromino
    int TetrisVector::numberOfMoves() const{
        return total_move;
    }

} // end namespace
