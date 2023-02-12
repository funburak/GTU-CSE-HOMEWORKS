#include <iostream>
#include <string>
#include <deque>
#include <thread>
#include <chrono>


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
    string file1("vectortetris.txt");
    string file2("1dtetris.txt");
    string file3("adapttetris.txt");

    vector<Tetromino> t1;
    t1.push_back(Piece::T);
    t1.push_back(Piece::J);
    t1.push_back(Piece::O);

    TetrisVector tv(20,20);
    tv.createBoard();
    tv+=t1[0];
    tv.animate(t1[0],5,'r',1,'l');
    tv+=t1[1];
    tv.animate(t1[1],3,'r',1,'l');
    tv+=t1[2];
    tv.animate(t1[2],3,'r',0,'l');
    cout << "This board written to vectortetris.txt. (Waiting 2 seconds...)" << endl;
    tv.writeToFile(file1);
    this_thread::sleep_for(chrono::milliseconds(2000)); // Sleeps 2 seconds

    vector<Tetromino> t2;
    t2.push_back(Piece::T);
    t2.push_back(Piece::J);
    t2.push_back(Piece::O);

    TetrisArray1D t1D(20,20);
    t1D.createBoard();
    t1D+=t2[0];
    t1D.animate(t2[0],5,'r',1,'l');
    t1D+=t2[1];
    t1D.animate(t2[1],3,'r',1,'l');
    t1D+=t2[2];
    t1D.animate(t2[2],3,'r',0,'l');
    cout << "This board has written to 1dtetris.txt. (Waiting 2 seconds...)" << endl;
    t1D.writeToFile(file2);
    this_thread::sleep_for(chrono::milliseconds(2000)); // Sleeps 2 seconds

    vector<Tetromino> t3;
    t3.push_back(Piece::T);
    t3.push_back(Piece::J);
    t3.push_back(Piece::O);

    TetrisAdapter<deque<deque<char>>> ta(20,20);
    ta.createBoard();
    ta+=t3[0];
    ta.animate(t3[0],5,'r',1,'l');
    ta+=t3[1];
    ta.animate(t3[1],3,'r',1,'l');
    ta+=t3[2];
    ta.animate(t3[2],3,'r',0,'l');
    cout << "This board has written to adapttetris.txt" << endl;
    ta.writeToFile(file3);
    
    return 0;
}