#include <iostream>

#include "tetromino.h"
#include "tetris.h"

using namespace std;
using namespace Tetrominos;
using namespace TETRIS;


int main(){
    int row_size,col_size;
    int rotation_count;
    char rotation;
    char move_direction;
    int move_count;
    while(1){
        cout << "Enter row and column size of the board" << endl;
        if(cin >> row_size >> col_size && row_size > 0 && col_size > 0){
            break;
        }
        else{
            cout << "Illegal values. Please try again." << endl;
            cin.clear();
            cin.ignore(31,'\n');
        }
    }
    Tetris board(row_size,col_size);
    do{
        char p;
        static int i=0;
        while(1){
            cout << "Enter tetromino type. 'R' for random and 'Q' to quit." << endl;
            if(cin >> p && ((p == 'I') ||(p == 'O') ||(p == 'T') ||(p == 'L') ||(p == 'J') ||(p == 'S') ||(p == 'Z') ||(p == 'R') || (p == 'q') || (p == 'Q'))){
                break;
            }
            else{
                cout << "Illegal tetromino type. Please enter a valid type!" << endl;
                cin.clear();
                cin.ignore(31,'\n');
            }
        }
        if(p == 'Q' || p == 'q'){
            cout << "Exiting..." << endl;
            break;
        }
        else{
            Tetromino **tetros;
            tetros = new Tetromino*[50];

            for(int index=0; index<50; ++index){
                tetros[index] = new Tetromino(static_cast<Piece>(p));
            }
            cout << "Entered tetromino shape." << endl;
            tetros[i]->print();
        while(1){
            cout << "Please enter the rotation direction 'l' for left and 'r' for right and enter the rotation count " << endl;
            if(cin >> rotation >> rotation_count && (rotation == 'l' || rotation == 'r') && (rotation_count >= 0)){
                break;
            }
            else{
                cout << "Illegal values please try again!!!" << endl;
                cin.clear();
                cin.ignore(31,'\n');
            }
        }

        while(1){
            cout << "Enter the move direction 'l' for left and 'r' for right and enter the move count" << endl;
            if((cin >> move_direction >> move_count) && (move_direction == 'l' || move_direction == 'r') && (move_direction > 0) || 
                (move_direction <= board.getCol()/2-1)){
                break;
            }
            else{
                cout << "Illegal values. Please try again!!!" << endl;
                cin.clear();
                cin.ignore(31,'\n');
            } 
        }
            board+=*tetros[i];
            board.Animate(*tetros[i],move_direction,move_count,rotation,rotation_count);
            i++;
        }

    }while(1);
    
    return 0;
}