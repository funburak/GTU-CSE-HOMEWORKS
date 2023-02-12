#include <iostream>
#include <vector>

#include "tetromino.h"

using namespace std;

namespace tetros{

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
        std::vector<std::vector<char>> temp(getRow(), std::vector<char>(getCol()));
            if (direction == 'l') {
                for (int r = 0; r < getRow(); ++r) {
                    for (int c = 0; c < getCol(); ++c) {
                        temp[getRow() - 1 - c][r] = shape[r][c];
                    }
                }
            } else if (direction == 'r') {
                for (int r = 0; r < getRow(); ++r) {
                    for (int c = 0; c < getCol(); ++c) {
                        temp[c][getCol() - 1 - r] = shape[r][c];
                    }
                }
            }
            shape = temp;
    }

    vector<vector<char> > Tetromino::getShape(){
        return shape;
    }

    int Tetromino::getRow() const{
        return shape.size();
    }

    int Tetromino::getCol() const{
        return shape[0].size();
    }

} // end namespace