// Written by James Mok

#ifndef DIAG_HPP
#define DIAG_HPP

#include "Board-KorideMok.hpp"

class DiagBoard : public Board {
    public:
        DiagBoard() = default;
        DiagBoard(short, short, ifstream&);
        ~DiagBoard() = default; //{delete[] Board::bd; }; //TODO check this
        void createDiagonal();
};


#endif
