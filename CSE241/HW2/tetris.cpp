#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "tetris.hpp"

using namespace std;

Tetris::Tetris(){
    board_row = 0;
    board_col = 0;
}

Tetris::Tetris(int row, int col): board_row(row+2), board_col(col+2){
    
}

void Tetris::createBoard(){
    vector<vector<char> > Temp(board_row,vector<char>(board_col,' '));
    for(int r=0; r<board_row; ++r){
        for(int c=0; c<board_col; ++c){
            if(r == 0 || r==board_row-1 || c == 0 || c == board_col-1){
                Temp[r][c] = '#';
            }            
        }
    }
    Board = Temp;
}

void Tetris::Draw() const{
    for(int r=0; r<board_row; ++r){
        for(int c=0; c<board_col; ++c){
            cout << Board[r][c];
        }
        cout << endl;
    }
}

void Tetris::Add(vector<vector<char> > tetro){
    int mid_col = board_col / 2;
    for(int r=0; r<tetro.size(); ++r){
        for(int c=0; c<tetro[r].size(); ++c){
            Board[r+1][mid_col + c -1] = tetro[r][c];
        }
    }
}

void Tetris::DeleteAdd(vector<vector<char> > tetro){
    for(int r=0; r<tetro.size(); ++r){
        for(int c=0; c<tetro[r].size(); ++c){
                Board[r+1][board_col/2 + c -1] = ' ';
        }
    }
}

void Tetris::Animate(vector<vector<char> > tetro){
    int count = 0;
    static int bottom = board_row-1;
    static int best_row = 1;
    static int best_col = 1; 
    static int vertical_shape_count = 0;
    while(count <= bottom){
        //cout << "count = " << count << endl;
        this->Draw();
        this->DeleteAdd(tetro);

        for(int r=0; r<tetro.size(); ++r){
            for(int c=0; c<tetro[r].size(); ++c){
                Board[best_row+count+r][best_col+c] = ' ';
            }
        }
        for(int r=0; r<tetro.size(); ++r){
            for(int c=0; c<tetro[r].size(); ++c){
                Board[best_row+r+count+1][best_col+c] = tetro[r][c];
            }
        }

        this->Sleep();
        count++;
        if(tetro.size() + count >= bottom-1){ // When the shape hits bottom
            //cout << "break" << endl;
            break;
        }
    }
    best_col = best_col + tetro[0].size();
    //cout << best_col << endl;
    if(best_col >= board_col-2){
        best_row = 1;
        best_col = 1;
        bottom = board_row - 1 - 3;
    }
    this->Draw();
}

void Tetris::Sleep(){    
    this_thread::sleep_for(chrono::milliseconds(50)); // Sleeps 50 miliseconds
    cout << "\x1b[2J"; // Erases entire screen
    cout << "\x1b[H"; // Move cursor to home position (0,0)
}

bool Tetris::Fit(){
    if(Board[board_row-1][board_col-1] == ' ' && Board[board_row-2][board_col-2] == ' '){
        return true;
    }       
    return false;
}