#include "knight.h"


int main(int argc, char ** argv) {

    #ifdef USING_FILE
        freopen("output.txt", "w", stdout);
    #endif
        
    string file_input(argv[1]);
    int HP, level, remedy, maidenkiss, phoenixdown, rescue;
    adventureToKoopa(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);

    /*
    cout << __LINE__ << endl;
    cout << __FUNCTION__ << endl;
    cout << __FILE__ << endl;
    */
    return 0;
}