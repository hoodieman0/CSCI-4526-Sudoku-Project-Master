// Written by James Mok and Neelakanta Bharadwaj Koride

#pragma once

#include "tools.hpp"
#include "Square-KorideMok.hpp"
#include "Cluster-KorideMok.hpp"
#include "Frame-KorideMok.hpp"
#include "CanView.hpp"

enum class ClusterType {ROW=0, COLUMN, BOX, DIAGONAL, HBOX, VBOX};

class Board : public CanView{
    protected:
        short n; // Size of the puzzle
        Square* bd;
        ifstream& file;
        short left; //dead variable requested by intstructions
        vector<shared_ptr<Cluster>> buddies;

        void getPuzzle();
        void makeClusters();
        void createRow(const short row);
        void createCol(const short col);

    public:
        Board(short, short, ifstream&);
        ~Board(){ cout <<"~Destroying Board~" <<endl; delete[] bd; }

        Square& sub(const short row, const short col) const { return bd[(row - 1)* n + (col - 1)]; }
        void mark(const short row, const short col, const char val) const;
        char getMarkChar(int row, int col) const override { return sub(row, col).getValue(); };
        string getPossibilityString(int row, int col) const override { return sub(row, col).getPosListString(); }
        void restoreState(shared_ptr<Frame> frame);

        ostream& print(ostream&) const;
};



inline ostream& operator<<(ostream& out, Board& b){
    return b.print(out);
}