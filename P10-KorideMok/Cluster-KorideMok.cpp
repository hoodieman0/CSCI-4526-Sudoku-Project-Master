// Written by James Mok and Neelakanta Bharadwaj Koride

#include "Cluster-KorideMok.hpp"

// ---------------------------------------------------------------------
// Constructor for the Cluster class
// Preconditions: there is a valid array of Square objects
// Postconditions: adds the created cluster to each square in the array
Cluster::
Cluster(const string type, Square* arr[9]) : type(type){
    for (int index = 0; index < 9; index++){
        clstr[index] = arr[index];
        clstr[index]->addCluster(this);
    }
}

// ---------------------------------------------------------------------
// turns off the bit of the given value for all squares in the cluster
// Preconditions: board object exists
// Postconditions: State::poslist of each Square has its 'val' bit turned off
void Cluster::
shoop(const char val){
    const int n = val - '0';
    for (Square* square : clstr) square->turnOff(n);
}

// ---------------------------------------------------------------------
// Checks to see if val is not used in other squares
// Preconditions: board object exists
// Postconditions: return false if val appears in another square, else return true
const bool Cluster::
isValid(const char val) const{
    for (Square* square : clstr) {
        if (square->getValue() == val) return false;
    }
    return true;
}

// ---------------------------------------------------------------------
// Prints the Cluster values in a human-readable format
// Preconditions: board object exists
// Postconditions: Sends the cluster to the ostream
ostream& Cluster::
print(ostream& out) const {
    out << type <<endl;
    for (Square* square : clstr) out <<*square <<endl;
    return out;
}
