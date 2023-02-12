#ifndef ABSTRACTTETRIS_H
#define ABSTRACTTETRIS_H

#include <iostream>
#include <string>

#include "tetromino.h"

using namespace std;
using namespace tetros;

namespace AbsTetris{

    class AbstractTetris{
        public:
            virtual ~AbstractTetris() = default;

            virtual void draw()const = 0;
            virtual void readFromFile(const string filename) = 0;
            virtual void writeToFile(const string filename) = 0;
            virtual void operator+=(Tetromino& other) = 0;
            virtual void animate(Tetromino &t,int move_c, char move_d, int rotate_c, char rotate_d) = 0;
            virtual void deleteAdd(const Tetromino &t) = 0;
            virtual void sleep()const = 0;
            virtual char lastMove() const = 0;
            virtual int numberOfMoves() const = 0;

    };
} // end namespace

#endif // ABSTRACTTETRIS_H