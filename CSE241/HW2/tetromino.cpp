#include <iostream>
#include <vector>

#include "tetromino.hpp"

using namespace std;

Tetromino::Tetromino(){ /* empty */}

Tetromino::Tetromino(Piece piece): piece_type(piece){
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
        shape.push_back({' ',' ',' '});
        shape.push_back({'T','T','T'});
        shape.push_back({' ','T',' '});        
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
        shape.push_back({' ',' ',' '});
        shape.push_back({' ','S','S'});
        shape.push_back({'S','S',' '});        
    }
    else if(piece_type == Piece::Z){
        shape.push_back({' ',' ',' '});
        shape.push_back({'Z','Z',' '});
        shape.push_back({' ','Z','Z'});        
    }
    else if(piece_type == Piece::R){
        srand(time(nullptr));
        int random = rand() % 7 +1;
        cout << "random = " << random << endl;
        switch(random){
            case 1:
                shape.push_back({' ',' ',' ',' '});
                shape.push_back({' ',' ',' ',' '});
                shape.push_back({' ',' ',' ',' '});
                shape.push_back({'I','I','I','I'});
                break;
            case 2:
                shape.push_back({'O','O'});
                shape.push_back({'O','O'});
                break;
            case 3:
                shape.push_back({' ',' ',' '});
                shape.push_back({'T','T','T'});
                shape.push_back({' ','T',' '});
                break;
            case 4:
                shape.push_back({' ','J',' '});
                shape.push_back({' ','J',' '});
                shape.push_back({'J','J',' '});
                break;
            case 5:
                shape.push_back({'L',' ',' '});
                shape.push_back({'L',' ',' '});
                shape.push_back({'L','L',' '});
                break;
            case 6:
                shape.push_back({' ',' ',' '});
                shape.push_back({' ','S','S'});
                shape.push_back({'S','S',' '});
                break;
            case 7:
                shape.push_back({' ',' ',' '});
                shape.push_back({'Z','Z',' '});
                shape.push_back({' ','Z','Z'});
                break;       
        }
    }
}

void Tetromino::print() const{
    for(int r=0; r<shape.size(); ++r){
        for(int c=0; c<shape[r].size(); ++c){
            cout << shape[r][c];
        }
        cout << endl;
    }
}

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

vector<vector<char> > Tetromino::getShape(){
    return shape;
}