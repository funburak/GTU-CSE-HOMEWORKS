#include <iostream>
#include <string>
#include <vector>

#include "tetromino.h"
#include "AbstractTetris.h"
#include "TetrisVector.h"
#include "Tetris1D.h"
#include "TetrisAdapter.h"


using namespace std;
using namespace tetros;
using namespace AbsTetris;
using namespace VectTetris;
using namespace Tetris1D;
using namespace AdapTetris;

int main(){
    int selection;
    int row,col;
    cout << "Please select from the menu!" << endl;
    do{
        cout << "1. TetrisVector class" << endl;
        cout << "2. Tetris1D class" << endl;
        cout << "3. TetrisAdapter class" << endl;
        cout << "4. QUIT" << endl;

        cin >> selection;
            if(selection == 1){
                char p;
                string file("game.txt");
                try{
                    cout << "Please enter the boards size: ";
                    cin >> row >> col;
                    if(row <= 0 || col <= 0){
                        throw out_of_range("Size cannot be less than or equal to 0.");
                    }
                }
                catch(out_of_range){
                    cerr << "Exception occured. Size cannot be less than or equal to 0." << endl;
                    break;
                }
                    TetrisVector tv(row,col);
                    tv.createBoard();

                    while(1){
                    int i=0;
                    while(1){
                    cout << "Please enter the tetromino type. R for random. Q to return to menu: ";
                    if(cin >> p && ((p == 'I') ||(p == 'O') ||(p == 'T') ||(p == 'L') ||(p == 'J') ||(p == 'S') ||(p == 'Z') ||(p == 'R') || (p == 'q') || (p == 'Q'))){
                        break;
                    }
                    else{
                        cout << "Illegal value. Please try again." << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }
                    }
                    if(p == 'q' || p == 'Q'){
                        cout << "Returning to menu." << endl;
                        break;
                    }
                    vector<Tetromino> t;
                    t.push_back(static_cast<Piece>(p));

                    char move_direction, rotate_direction;
                    int move_count,rotate_count;
                    while(1){
                    cout << "Please enter the rotate direction and count:" << endl;
                    if(cin >> rotate_direction >> rotate_count && (rotate_direction == 'l' || rotate_direction == 'r') && (rotate_count >= 0)){
                        break;
                    }
                    else{
                        cout << "Illegal values please try again!!!" << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }   
                    }
                    while(1){
                    cout << "Please enter the move direction and count:" << endl;
                    if((cin >> move_direction >> move_count) && (move_direction == 'l' || move_direction == 'r') && (move_direction > 0)){
                        break;
                    }
                    else{
                        cout << "Illegal values. Please try again!!!" << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }
                    }
                    tv+=t[i];
                    tv.animate(t[i],move_count,move_direction,rotate_count,rotate_direction);
                    i++;
                    cout << "Total moves: " << tv.numberOfMoves() << endl;
                    cout << "Writing game to the game.txt file." << endl;
                    tv.writeToFile(file);
                    if(tv.lastMove() == 'd'){
                        cout << "Last move was down!" << endl;
                    }
                    }
            }
            else if(selection == 2){
                char p;
                string file2("game2.txt");
                try{
                    cout << "Please enter the boards size: ";
                    cin >> row >> col;
                    if(row <= 0 || col <= 0){
                        throw out_of_range("Size cannot be less than or equal to 0.");
                    }
                }
                catch(out_of_range){
                    cerr << "Exception occured. Size cannot be less than or equal to 0." << endl;
                    break;
                }
                TetrisArray1D t1(row,col);
                t1.createBoard();

                while(1){
                    int i=0;
                    char p;
                    while(1){
                    cout << "Please enter the tetromino type. R for random. Q to return to menu: ";
                    if(cin >> p && ((p == 'I') ||(p == 'O') ||(p == 'T') ||(p == 'L') ||(p == 'J') ||(p == 'S') ||(p == 'Z') ||(p == 'R') || (p == 'q') || (p == 'Q'))){
                        break;
                    }
                    else{
                        cout << "Illegal value. Please try again." << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }
                    }
                    if(p == 'q' || p == 'Q'){
                        cout << "Returning to menu." << endl;
                        break;
                    }
                    vector<Tetromino> t;
                    t.push_back(static_cast<Piece>(p));

                    char move_direction, rotate_direction;
                    int move_count,rotate_count;
                    while(1){
                    cout << "Please enter the rotate direction and count:" << endl;
                    if(cin >> rotate_direction >> rotate_count && (rotate_direction == 'l' || rotate_direction == 'r') && (rotate_count >= 0)){
                        break;
                    }
                    else{
                        cout << "Illegal values please try again!!!" << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }   
                    }
                    while(1){
                    cout << "Please enter the move direction and count:" << endl;
                    if((cin >> move_direction >> move_count) && (move_direction == 'l' || move_direction == 'r') && (move_direction > 0)){
                        break;
                    }
                    else{
                        cout << "Illegal values. Please try again!!!" << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }
                    }
                    t1+=t[i];
                    t1.animate(t[i],move_count,move_direction,rotate_count,rotate_direction);
                    i++;
                    cout << "Total moves: " << t1.numberOfMoves() << endl;
                    cout << "Writing game to the game2.txt file." << endl;
                    t1.writeToFile(file2);
                    if(t1.lastMove() == 'd'){
                        cout << "Last move was down!" << endl;
                    }
                }

            }
            else if(selection == 3){
                char p;
                string file3("game3.txt");
                try{
                    cout << "Please enter the boards size: ";
                    cin >> row >> col;
                    if(row <= 0 || col <= 0){
                        throw out_of_range("Size cannot be less than or equal to 0.");
                    }
                }
                catch(out_of_range){
                    cerr << "Exception occured. Size cannot be less than or equal to 0." << endl;
                    break;
                }

                TetrisAdapter<vector<vector<char>>> ta(row,col);
                ta.createBoard();

                while(1){
                    int i=0;
                    while(1){
                    cout << "Please enter the tetromino type. R for random. Q to return to menu: ";
                    if(cin >> p && ((p == 'I') ||(p == 'O') ||(p == 'T') ||(p == 'L') ||(p == 'J') ||(p == 'S') ||(p == 'Z') ||(p == 'R') || (p == 'q') || (p == 'Q'))){
                        break;
                    }
                    else{
                        cout << "Illegal value. Please try again." << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }
                    }
                    if(p == 'q' || p == 'Q'){
                        cout << "Returning to menu." << endl;
                        break;
                    }
                    vector<Tetromino> t;
                    t.push_back(static_cast<Piece>(p));

                    char move_direction, rotate_direction;
                    int move_count,rotate_count;
                    while(1){
                    cout << "Please enter the rotate direction and count:" << endl;
                    if(cin >> rotate_direction >> rotate_count && (rotate_direction == 'l' || rotate_direction == 'r') && (rotate_count >= 0)){
                        break;
                    }
                    else{
                        cout << "Illegal values please try again!!!" << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }   
                    }
                    while(1){
                    cout << "Please enter the move direction and count:" << endl;
                    if((cin >> move_direction >> move_count) && (move_direction == 'l' || move_direction == 'r') && (move_direction > 0)){
                        break;
                    }
                    else{
                        cout << "Illegal values. Please try again!!!" << endl;
                        cin.clear();
                        cin.ignore(31,'\n');
                    }

                    }
                    ta+=t[i];
                    ta.animate(t[i],move_count,move_direction,rotate_count,rotate_direction);
                    i++;
                    cout << "Total moves: " << ta.numberOfMoves() << endl;
                    cout << "Writing game to the game3.txt file." << endl;
                    ta.writeToFile(file3);
                    if(ta.lastMove() == 'd'){
                        cout << "Last move was down!" << endl;
                    }
                }
            }

            else if(selection == 4){
                cout << "EXITING..." << endl;
                break;
            }
            else{
                cout << "Please select valid item from the menu." << endl;
            }
    }while(selection !=4);

    return 0;
}