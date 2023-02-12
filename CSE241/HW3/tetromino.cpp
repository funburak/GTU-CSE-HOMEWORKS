#include <iostream>

#include "tetromino.h"

using namespace std;

namespace Tetrominos{

    Tetromino::Tetromino(){ /* Empty*/}

    Tetromino::Tetromino(Piece piece) : piece_type(piece){
        if(piece_type == Piece::I){
            row = 4;
            col = 4;
            shape = new char*[row];
            for(int i=0; i<row; ++i){
                shape[i] = new char[row];
            }
            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    if(r == 3){
                        shape[r][c] = 'I';
                    }
                    else{
                        shape[r][c] = ' ';
                    }
                }
            }
        }
        else if(piece_type == Piece::O){
            row = 2;
            col = 2;
            shape = new char*[row];
            for(int i=0; i<row; ++i){
                shape[i] = new char[row];
            }
            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    shape[r][c] = 'O';
                }
            }
        }
        else if(piece_type == Piece::T){
            row = 3;
            col = 3;
            shape = new char*[row];
            for(int i=0; i<row; ++i){
                shape[i] = new char[row];
            }
            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    if(r == 0 || (r == 1 && c == 1)){
                        shape[r][c] = 'T';
                    }
                    else{
                        shape[r][c] = ' ';
                    }
                }
            }
        }
        else if(piece_type == Piece::J){
            row = 3;
            col = 3;
            shape = new char*[row];
            for(int i=0; i<row; ++i){
                shape[i] = new char[row];
            }
            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    if((r == 2 && c == 0) || (c == 1)){
                        shape[r][c] = 'J';
                    }
                    else{
                        shape[r][c] = ' ';
                    }
                }
            }
        }
        else if(piece_type == Piece::L){
            row = 3;
            col = 3;
            shape = new char*[row];
            for(int i=0; i<row; ++i){
                shape[i] = new char[row];
            }
            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    if((c == 0) || (r == 2 && c == 1)){
                        shape[r][c] = 'L';
                    }
                    else{
                        shape[r][c] = ' ';
                    }
                }
            }
        }
        else if(piece_type == Piece::S){
            row = 3;
            col = 3;
            shape = new char*[row];
            for(int i=0; i<row; ++i){
                shape[i] = new char[row];
            }
            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    if((r == 0 && (c == 1 || c == 2)) || (r == 1) && (c == 0 || c == 1)){
                        shape[r][c] = 'S';
                    }
                    else{
                        shape[r][c] = ' ';
                    }
                }
            }
        }
        else if(piece_type == Piece::Z){
            row = 3;
            col = 3;
            shape = new char*[row];
            for(int i=0; i<row; ++i){
                shape[i] = new char[row];
            }
            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    if((r == 0 && (c == 0 || c == 1)) || (r == 1) && (c == 1 || c == 2)){
                        shape[r][c] = 'Z';
                    }
                    else{
                        shape[r][c] = ' ';
                    }
                }
            }
        }
        else if(piece_type == Piece::R){
            srand(time(nullptr));
            int random = rand() % 7 + 1;
            switch(random){
                case 1: // Shape I
                    row = 4;
                    col = 4;
                    shape = new char*[row];
                    for(int i=0; i<row; ++i){
                        shape[i] = new char[row];
                    }
                    for(int r=0; r<row; ++r){
                        for(int c=0; c<col; ++c){
                            if(r == 3){
                                shape[r][c] = 'I';
                            }
                            else{
                                shape[r][c] = ' ';
                            }
                        }
                    }
                break;
                case 2: // Shape O
                    row = 2;
                    col = 2;
                    shape = new char*[row];
                    for(int i=0; i<row; ++i){
                        shape[i] = new char[row];
                    }
                    for(int r=0; r<row; ++r){
                        for(int c=0; c<col; ++c){
                            shape[r][c] = 'O';
                        }
                    }
                break;
                case 3:// Shape T
                    row = 3;
                    col = 3;
                    shape = new char*[row];
                    for(int i=0; i<row; ++i){
                        shape[i] = new char[row];
                    }
                    for(int r=0; r<row; ++r){
                        for(int c=0; c<col; ++c){
                            if(r == 0 || (r == 1 && c == 1)){
                                shape[r][c] = 'T';
                            }
                            else{
                                shape[r][c] = ' ';
                            }
                        }
                    }
                break;
                case 4: // Shape J
                    row = 3;
                    col = 3;
                    shape = new char*[row];
                    for(int i=0; i<row; ++i){
                        shape[i] = new char[row];
                    }
                    for(int r=0; r<row; ++r){
                        for(int c=0; c<col; ++c){
                            if((r == 2 && c == 0) || (c == 1)){
                                shape[r][c] = 'J';
                            }
                            else{
                                shape[r][c] = ' ';
                            }
                        }
                    }
                break;
                case 5: // Shape L
                    row = 3;
                    col = 3;
                    shape = new char*[row];
                    for(int i=0; i<row; ++i){
                        shape[i] = new char[row];
                    }
                    for(int r=0; r<row; ++r){
                        for(int c=0; c<col; ++c){
                            if((c == 0) || (r == 2 && c == 1)){
                                shape[r][c] = 'L';
                            }
                            else{
                                shape[r][c] = ' ';
                            }
                        }
                    }
                break;
                case 6: // Shape S
                    row = 3;
                    col = 3;
                    shape = new char*[row];
                    for(int i=0; i<row; ++i){
                        shape[i] = new char[row];
                    }
                    for(int r=0; r<row; ++r){
                        for(int c=0; c<col; ++c){
                            if((r == 0 && (c == 1 || c == 2)) || (r == 1) && (c == 0 || c == 1)){
                                shape[r][c] = 'S';
                            }
                            else{
                                shape[r][c] = ' ';
                            }
                        }
                    }    
                break;
                case 7: // Shape Z
                    row = 3;
                    col = 3;
                    shape = new char*[row];
                    for(int i=0; i<row; ++i){
                        shape[i] = new char[row];
                    }
                    for(int r=0; r<row; ++r){
                        for(int c=0; c<col; ++c){
                            if((r == 0 && (c == 0 || c == 1)) || (r == 1) && (c == 1 || c == 2)){
                                shape[r][c] = 'Z';
                            }
                            else{
                                shape[r][c] = ' ';
                            }
                        }
                    }
                break;
            }
        }
    }


    Tetromino::~Tetromino(){
        for(int i=0; i<getRow(); ++i){
            delete [] shape[i];
        }
        delete[] shape;
        shape = nullptr;
    }

    void Tetromino::print() const{ // Prints out the shape of Tetromino
        for(int r=0; r<getRow(); ++r){
            for(int c=0; c<getCol(); ++c){
                cout << shape[r][c];
            }
            cout << endl;
        }
    }

    void Tetromino::rotate(char direction){ // Rotates the tetromino clockwise or counter-clockwise
        if(direction == 'l'){
            char **temp = new char*[row];
            for(int i=0; i<row; ++i){
                temp[i] = new char[row];
            }

            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    temp[row-1-c][r] = shape[r][c];
                }
            }

            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    shape[r][c] = temp[r][c];
                }
            }
            for(int i=0; i<getRow(); ++i){
                delete [] temp[i];
            }
            delete [] temp;
            temp = nullptr;
        }
        else if(direction == 'r'){
            char **temp2 = new char*[row];
            for(int i=0; i<row; ++i){
                temp2[i] = new char[row];
            }

            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    temp2[c][col-1-r] = shape[r][c];
                }
            }

            for(int r=0; r<row; ++r){
                for(int c=0; c<col; ++c){
                    shape[r][c] = temp2[r][c];
                }
            }
            for(int i=0; i<getRow(); ++i){
                delete [] temp2[i];
            }
            delete [] temp2;
            temp2 = nullptr;
        }
    }

    int Tetromino::getRow() const{
        return row;
    }

    int Tetromino::getCol() const{
        return col;
    }

    char **Tetromino::getShape() const{
        return shape;
    }
    

} // end namespace