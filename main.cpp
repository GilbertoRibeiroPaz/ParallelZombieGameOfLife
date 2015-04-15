#include <iostream>
#include <vector>
#include "parallelzombiegameoflife.h"
#include "gameconfig.h"

using namespace std;

int main(int argc, char** argv)
{

    GameConfig gc;
    //cout << gc;


    vector< vector<int> > gridConfig = {
        { 0, 0, 1, 1 },
        { 1, 0, 0, 1 },
        { 0, 1, 0, 0 },
        { 1, 1, 0, 1 }
    };
    //gc.printToFile(gridConfig);
    /*
    ParallelZombieGameOfLife game(gridConfig.size(), 3, gridConfig);
    game.run();
    */
    return 0;
}



