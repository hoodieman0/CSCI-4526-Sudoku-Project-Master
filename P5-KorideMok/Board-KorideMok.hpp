// Written by James Mok and Neelakanta Bharadwaj Koride

#include "tools.hpp"
#include "Square-KorideMok.hpp"
#include "Cluster-KorideMok.hpp"
#pragma once

enum class ClusterType {ROW, COLUMN, BOX};

class Board{
    private:
        int n = 9; // Size of the puzzle
        Square * bd;
        ifstream& file;
        short left = 81;
        vector<Cluster*> buddies;

        void getPuzzle();
        void makeClusters();
        void createRow(short);
        void createCol(short);
        void createBox(short, short);

    public:
        Board(int, ifstream&);
        ~Board(){ cout <<"~Destroying Board~" <<endl; delete[] bd; }
        Square& sub(int r, int c){ return bd[(r - 1)* n + (c - 1)]; }
        void mark(int, int, char);
        ostream& print(ostream&);
};

inline ostream& operator<<(ostream& out, Board& b){
    return b.print(out);
}