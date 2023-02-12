#include <iostream>
#include <vector>
#include <cstdlib> // For exit function
#include "Tetrominos.h"

using namespace std;

Tetromino::Tetromino(){/* Left empty intentionally*/}

Tetromino::Tetromino(Piece piece) : piece_type(piece){}

void Tetromino::rotate(char direction){
    if(direction == 'l' || direction == 'L'){ // Rotating towards counter-clockwise
        if(piece_type == Piece::I){ // For I shape the algorithm for else part doesnt work so i fix it like this
            vector<vector<char>> temp{shape[0].size(),vector<char>(shape.size()+1,' ')};
            for(int r=0; r<shape.size(); ++r){
                for(int c=0; c<shape[r].size(); ++c){    
                    int row,col;                
                    if(shape[r][c] == 'I'){
                        row = c;
                        col = shape.size()-r-1;
                        temp[row][col] = 'I';
                    }
                }
            }
            shape = temp;
        }
        else{
            for(int r=0; r<shape.size()/2; ++r){
                for(int c=0; c<shape.size()-r-1; ++c){
                    int temp = shape[r][c];
                    shape[r][c] = shape[c][shape.size()-1-r];
                    shape[c][shape.size()-1-r] = shape[shape.size()-1-r][shape.size()-1-c];
                    shape[shape.size()-1-r][shape.size()-1-c] = shape[shape.size()-c-1][r];
                    shape[shape.size()-c-1][r] = temp;
                }
            }
        } 
    }
    else if(direction == 'r' || direction == 'R'){ // Rotating towards clockwise
        for(int r=0; r<shape.size()/2; ++r){
            for(int c=0; c<shape.size()-1-r; ++c){
                int temp = shape[r][c];
                shape[r][c] = shape[shape.size()-1-c][r];
                shape[shape.size()-1-c][r] = shape[shape.size()-1-r][shape.size()-1-c];
                shape[shape.size()-1-r][shape.size()-1-c] = shape[c][shape.size()-1-r];
                shape[c][shape.size()-1-r] = temp;
            }
        }
    }
}

void Tetromino::print() const{
    for(int i=0; i<shape.size(); ++i){
        for(int j=0; j<shape[i].size(); ++j){
            cout << shape[i][j];
        }
        cout << endl;
    }
}

bool Tetromino::canFit(const Tetromino &other, char position) const{
    return true;
}


void Tetromino::createShape(){
    if(piece_type == Piece::I){
        shape.push_back({'I','I','I','I'});
        shape.push_back({' ',' ',' ',' '});
        shape.push_back({' ',' ',' ',' '});
        shape.push_back({' ',' ',' ',' '});
    }
    else if(piece_type == Piece::O){
        shape.push_back({'O','O'});
        shape.push_back({'O','O'});
    }
    else if(piece_type == Piece::T){
        shape.push_back({'T','T','T'});
        shape.push_back({' ','T',' '});
        shape.push_back({' ',' ',' '});        
    }
    else if(piece_type == Piece::J){
        shape.push_back({' ','J',' '});
        shape.push_back({' ','J',' '});
        shape.push_back({'J','J',' '});        
    }
    else if(piece_type == Piece::L){
        shape.push_back({'L',' ',' '});
        shape.push_back({'L',' ',' '});
        shape.push_back({'L','L',' '});        
    }
    else if(piece_type == Piece::S){
        shape.push_back({' ','S','S'});
        shape.push_back({'S','S',' '});
        shape.push_back({' ',' ',' '});        
    }
    else if(piece_type == Piece::Z){
        shape.push_back({'Z','Z',' '});
        shape.push_back({' ','Z','Z'});
        shape.push_back({' ',' ',' '});        
    }
}

void Tetromino::createBoard(){
    vector<vector<char>> Board(20,vector<char>(20)); // a 20x20 board for the tetrominos to fill in
    for(int r=0; r<4; ++r){
        for(int c=0; c<20; ++c){
            Board[r][c] = shape[r][c];
        }
        cout << endl;
    }
    for(int r=0; r<4; ++r){
        for(int c=0; c<20; ++c){
            cout << Board[r][c];
        }
    }
}