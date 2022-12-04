// Written by James Mok and Neelakanta Bharadwaj Koride

#include "Game-KorideMok.hpp"

const string Game::
menu[7] = {"Mark", "Turn Off", "Undo", "Redo", "Save", "rEstore", "Quit"};

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
    switch(toupper(gameType)){
        case 'T': n = 9; clstr = 27; puzzle = new Board(n, clstr, file);
        case 'D': n = 9; clstr = 29; puzzle = new DiagBoard(n, clstr, file); break;
        case 'S': n = 6; clstr = 18; puzzle = new Board(n, clstr, file); break;
    }
}


// ---------------------------------------------------------------------
// Runs the game
// Precondition: Game object exists
// Postcondition: Displays the menu and calls possible options until quit is called
void Game::
run(){
    const static char legal[] { "MmTtUuRrSsEeQq" };
    Viewer fancyView(9, 9, *puzzle);
    Stack undo, redo;
    short r, c;
    char value;
    Frame* frame;
    State arr[81];
    string fileName;
    ofstream saveFile;
    ifstream inputFile;

    for(;;){
        fancyView.show(cout);
        cout <<"\nWhat Would You Like To Do? " <<endl;
        char x = menu_c("Menu", 7, menu, legal);
        switch (toupper(x)) {
            case 'P': cout <<*puzzle <<endl; continue; //continues the for loop

            case 'M':
                cout <<"Input 'Row' 'Column' 'Value': ";
                cin >> r >> c >> value;
                try{ puzzle->mark(r, c, value); }
                catch(GameException& e) { cout <<e << endl; continue; }

                
                for (int row = 0; row < n; row++){
                    for (int col = 0; col < n; col++){
                        arr[row+col] = puzzle->sub(row+1, col+1).getState();
                    }
                }
                frame = new Frame(arr);
                undo.push(frame);
                redo.zap();
                continue; 

            case 'T':
                cout <<"Input 'Row' 'Column' 'Value': ";
                cin >> r >> c >> value; 
                puzzle->sub(r, c).changeBit(value - '0');

                for (int row = 0; row < n; row++){
                    for (int col = 0; col < n; col++){
                        arr[row+col] = puzzle->sub(row+1, col+1).getState();
                    }
                }
                frame = new Frame(arr);
                undo.push(frame);
                redo.zap();
                continue;

            case 'U':
                if (undo.size() < 2) { cout <<"Not Enough Moves Has Been Made!" <<endl; continue; }

                frame = undo.top();
                undo.pop();
                redo.push(frame);
                puzzle->restoreState(frame);
                continue;

            case 'R': continue;
                if (redo.size() == 0) { cout <<"No Moves To Redo!" <<endl; continue; }

                frame = redo.top();
                redo.pop();
                undo.push(frame);
                puzzle->restoreState(frame);
                continue;

            case 'S': 
                cout <<"Type The Name Of The File To Save To: ";
                cin>> fileName;
                saveFile.open(fileName);
                undo.top()->serialize(saveFile);
                cout <<"Game Saved Successfully!" <<endl;
                continue;

            case 'E': 
                cout <<"Type The Name Of The File To Restore: ";
                cin>> fileName;
                inputFile.open(fileName);
                frame = new Frame();
                frame->realize(inputFile);
                undo.zap();
                redo.zap();
                puzzle->restoreState(frame);
                cout <<"Game Restored Successfully!" <<endl;
                continue;

            case 'Q': return;
        }
    }
}