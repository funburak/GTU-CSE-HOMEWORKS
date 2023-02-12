#include <iostream>
#include <cstdlib>
#include <vector>
#include "Tetrominos.h"

using namespace std;


int main(){
    int piece_count;
    char types;
    cout << "How many tetrominos?\n";
    cin >> piece_count;

    vector<Tetromino> T; // Vector of tetromino class type
    cout << "What are the types?\n";
    for(int i=0; i<piece_count; ++i){
        cin >> types;
        Piece type = static_cast<Piece>(types);
        if(type == Piece::I || type == Piece::O || type == Piece::T || type == Piece::J || type == Piece::L || type == Piece::S || type == Piece::Z){
            T.push_back(type);
        }
        else{
            cout << "Error! Wrong tetromino type. Terminating... " << endl;
            exit(-1);
        }
    }

    cout << "Your tetrominos" << endl;
    for(int j=0; j<T.size(); ++j){
        T[j].createShape();
        T[j].print();
        // I cannot do the best-fit part so I make these rotations part so that you can test them aswell
        // cout << "Right rotated shape is" << endl; 
        // T[j].rotate('r');
        //T[j].print();
        cout << "Left rotated shape is" << endl;
        T[j].rotate('l');
        T[j].print();
        cout << endl;
    }
    
    return 0;
}