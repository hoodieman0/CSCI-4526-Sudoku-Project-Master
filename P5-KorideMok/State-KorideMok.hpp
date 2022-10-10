// Written by James Mok and Neelakanta Bharadwaj Koride

#ifndef STATE_H
#define STATE_H

#include "tools.hpp"

class State {
private:
    short poslist = 0x3FE; //0011 1111 1110
    char value = '-';
    bool fixed = false; //is part of the original puzzle

public:
    State() { }//cout <<"Default State Constructor" << endl; }
    State(char);
    ~State() { }//cout <<"Default State Destructor" <<endl; }
    void mark(char);
    char getValue() { return value; }
    void turnOff(short);
    ostream& print(ostream&);
};

inline ostream& operator <<(ostream& out, State& st){
    return st.print(out);
}

#endif