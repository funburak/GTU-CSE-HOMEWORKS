#include <iostream>
#include <vector>

#include "tetris.hpp"
#include "tetromino.hpp"

using namespace std;

int main(){
    int row_size;
    int col_size;

    while (1){ // Valid entry check
        cout << "Please enter the row and columnn of the tetris board:" << endl;        
        if (cin >> row_size >> col_size && row_size > 0 && col_size > 0){ 
            break;
        }
        else{
            cout << "Illegal value. Please enter a valid value!" << endl;
            cin.clear();
            cin.ignore(31, '\n');
        }
    }
    Tetris tetris(row_size,col_size);
    tetris.createBoard();
    do{
        char p;
        int i = 0;
        while(1){ // Valid tetromino type entry check
            cout << "Enter the tetromino type.'R' for random and 'Q' for quit" << endl;
            if(cin >> p && ((p == 'I') ||(p == 'O') ||(p == 'T') ||(p == 'L') ||(p == 'J') ||(p == 'S') ||(p == 'Z') ||(p == 'R') || (p == 'q') || (p == 'Q'))){
                break;
            }
            else{
                cout << "Illegal tetromino type. Please enter a valid type!" << endl;
                cin.clear();
                cin.ignore(31,'\n');
            }
        }
        vector<Tetromino> T;
        T.push_back(static_cast<Piece>(p));
        if(p == 'q' || p == 'Q'){
            cout << "Exiting..." << endl;
            break;
        }
        
        tetris.Add(T[i].getShape());
        if(tetris.Fit()){ 
            tetris.Animate(T[i].getShape());
        }
        else{
            T[i].rotate('l');
            tetris.Animate(T[i].getShape());
        }
        i++;
    }while (1);
    
    return 0;
}