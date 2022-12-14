// Written by James Mok and Neelakanta Bharadwaj Koride

#ifndef STATE_H
#define STATE_H

#include "tools.hpp"
#include "Exceptions-KorideMok.hpp"

class State {
protected:
    short poslist = 0x3FE; //0011 1111 1110
    char value = '-';
    bool fixed = false; //is part of the original puzzle

public:
    State(char='-');
    ~State() = default;
    virtual void mark(char);
    char getValue() const { return value; }
    string getPosList() const;
    ostream& print(ostream&) const;
};

inline ostream& operator <<(ostream& out, State& st){
    return st.print(out);
}

#endif