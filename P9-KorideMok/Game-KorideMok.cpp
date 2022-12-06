// Written by James Mok and Neelakanta Bharadwaj Koride

#include "Game-KorideMok.hpp"

const string Game::
menu[7] = { "Mark", "Turn Off", "Undo", "Redo", "Save", "Restore", "Quit"};

// ---------------------------------------------------------------------
// Game Constructor
// Precondition: A valid game file exists
// Postcondition: Game object is created
Game::
Game(ifstream& file) : file(file) {
    short clstr;
    const static string types = "TtDdSs";
    file>>gameType;
    if (types.find(gameType) == string::npos) throw InvalidGameTypeException(gameType);
    switch(tolower(gameType)){
        case 't': n = 9; clstr = 27; puzzle = new Board(n, clstr, file);
        case 'd': n = 9; clstr = 29; puzzle = new DiagBoard(n, clstr, file); break;
        case 's': n = 6; clstr = 18; puzzle = new Board(n, clstr, file); break;
    }
}



// ---------------------------------------------------------------------
// Runs the game
// Precondition: Game object exists
// Postcondition: Displays the menu and calls possible options until quit is called
void Game::
run(){
    const static char legal[] { "MmTtUuRrSsQq" };
    Viewer fancyView(9, 9, *puzzle);
    for(;;){
        fancyView.show(cout);
        cout <<"\nWhat Would You Like To Do? " <<endl;
        char x = menu_c("Menu", 7, menu, legal);
        switch (toupper(x)) {
            case 'P': cout <<*puzzle <<endl; continue; //continues the for loop
            case 'M': Mark(); continue; 
            case 'T': TurnOff(); continue;
            case 'U': continue;
            case 'R': continue;
            case 'S': continue;
            case 'Q': return;
        }
    }
}

void Game::
Mark(){
    short r, c;
    char value;
    cout <<"Input 'Row' 'Column' 'Value': ";
    cin >> r >> c >> value;
    try{ puzzle->mark(r, c, value); }
    catch(GameException& e) { cout <<e << endl; }
}

void Game::
TurnOff(){
    short r, c;
    char value;
    cout <<"Input 'Row' 'Column' 'Value': ";
    cin >> r >> c >> value; 
    puzzle->sub(r, c).turnOff(value - '0');
}