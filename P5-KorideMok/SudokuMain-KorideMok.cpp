#include "UnitTests-KorideMok.hpp"
#include "tools.hpp"

// argv[1] is the file name used in Board class
int main(int argc, char* const argv[]){
    banner();

    if(argc != 2){ fatal("Incorrect Amount Of Arguments\nUsage: program-name input-file"); }

    ifstream ifs(argv[1]);
    if (!ifs.is_open()) { fatal("Unable To Open Input-File"); }

    testBoardFunctions(cout, argv[1]);

    cout <<"~Starting Game~" <<endl;
    Game obj(ifs);
    obj.run();
    cout <<"~Quitting Game~" <<endl;

    bye();
}