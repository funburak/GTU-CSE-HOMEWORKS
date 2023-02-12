// I cannot seperate the implementation for this template class.


#ifndef TETRISADAPTER_H
#define TETRISADAPTER_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "tetromino.h"
#include "AbstractTetris.h"
#include "TetrisAdapter.cpp"

using namespace std;
using namespace tetros;
using namespace AbsTetris;

namespace AdapTetris{
    template<class T>
    class TetrisAdapter : public AbstractTetris{
        public:
            TetrisAdapter(){
                board_row = 1;
                board_col = 1;
            }
            TetrisAdapter(int r, int c){
                board_row = r;
                board_col = c;
            }
            void createBoard(){
                using value_type = typename T::value_type;

                T temp(board_row,value_type(board_col,' '));
                for(int r=0; r<board_row; ++r){
                    for(int c=0; c<board_col; ++c){
                        if(r == 0 || r == board_row-1 || c == 0 || c == board_col-1){
                            temp[r][c] = '#';
                        }
                    }
                }
                board = temp;
            }
            void draw() const override{
                for(int r=0; r<board_row; ++r){
                    for(int c=0; c<board_col; ++c){
                        cout << board[r][c];
                    }
                    cout << endl;
                }
            }
            void readFromFile(const string filename) override{
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

            void writeToFile(const string filename) override{
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

            void operator+=(Tetromino &t) override{
                vector<vector<char>> temp = t.getShape();
                int mid_col = board_col / 2;
                for(int r=0; r<t.getRow(); ++r){
                    for(int c=0; c<t.getCol(); ++c){
                        board[r+1][mid_col+c-1] = temp[r][c];
                    }
                }
            }

            void deleteAdd(const Tetromino &t) override{
                for(int r=0; r<t.getRow(); ++r){
                    for(int c=0; c<t.getCol(); ++c){
                        board[r+1][board_col/2 + c - 1] = ' ';
                    }
                }
            }

            void animate(Tetromino &t,int move_c, char move_d, int rotate_c, char rotate_d) override{
                int count = 0;
                int bottom = board_row - 1;
                for(int i=0; i<rotate_c; ++i){
                    moves++;
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
                    moves++;
                    if(shape.size() + count >= bottom){
                        break;
                    }
                }
                this->draw();
            }

            void sleep() const override{
                this_thread::sleep_for(chrono::milliseconds(50)); // Sleeps 50 miliseconds
                cout << "\x1b[2J"; // Erases entire screen
                cout << "\x1b[H"; // Move cursor to home position (0,0)
            }
            char lastMove() const override{
                return 'd';
            }
            int numberOfMoves() const override{
                return moves;
            }

        private:
            T board;
            int board_row;
            int board_col;
            int moves = 0;
    };


} // end namespace


#endif // TETRISADAPTER_H